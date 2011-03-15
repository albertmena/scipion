/***************************************************************************
 *
 * Authors:    Sjors Scheres           scheres@cnb.csic.es (2004)
 *
 * Unidad de  Bioinformatica of Centro Nacional de Biotecnologia , CSIC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307  USA
 *
 *  All comments concerning this program package may be sent to the
 *  e-mail address 'xmipp@cnb.csic.es'
 ***************************************************************************/

#ifndef _ML2D_H
#define _ML2D_H

#include <sys/time.h>
#include <pthread.h>
#include <vector>
#include <data/fftw.h>
#include <data/fft.h>
#include <data/args.h>
#include <data/funcs.h>
#include <data/metadata_extension.h>
#include <data/image.h>
#include <data/geometry.h>
#include <data/filters.h>
#include <data/mask.h>
#include <data/ctf.h>
#include <data/threads.h>
#include <data/program.h>


#define SIGNIFICANT_WEIGHT_LOW 1e-8
#define SMALLANGLE 1.75
#define DATALINELENGTH 12

///******** Some macro definitions ****************
#define FOR_ALL_GLOBAL_IMAGES() \
    for (int imgno = 0; imgno < nr_images_global; imgno++)

#define FOR_ALL_LOCAL_IMAGES() \
    for (int imgno = myFirstImg; imgno <= myLastImg; imgno++)

#define IMG_LOCAL_INDEX (imgno - myFirstImg)
#define IMG_REAL_INDEX(imgno) img_id[(imgno)]
#define IMG_BLOCK(imgno) (imgno) % blocks

//For MPI
#define IS_MASTER (rank == 0)
//threads tasks
typedef enum { TH_EXIT, TH_ESI_REFNO, TH_ESI_UPDATE_REFNO, TH_RR_REFNO, TH_RRR_REFNO, TH_PFS_REFNO } ThreadTask;
//output types constants
typedef enum { OUT_BLOCK, OUT_ITER, OUT_FINAL, OUT_REFS, OUT_IMGS } OutputType;


class ModelML2D
{
public:
    /** Number of reference images */
    int n_ref;
    /** References images */
    std::vector < Image<double> > Iref;
    /** Sigma value for expected pixel noise */
    double sigma_noise;
    /** sigma-value for origin offsets */
    double sigma_offset;
    /** Vector containing estimated fraction for each model */
    std::vector<double> alpha_k;
    /** Vector containing estimated fraction for mirror of each model */
    std::vector<double> mirror_fraction;
    /** Average scales for each refno from do_norm */
    std::vector<double> scale;
    /** Sums of weights */
    double sumw_allrefs, sumw_allrefs2;
    /** Average height of the probability distribution at its maximum */
    double avePmax;
    /** the Log Likelihood */
    double LL;

    /** Dimension of images */
    int dim;
    /** Algorithmic variants */
    bool do_student, do_student_sigma_trick, do_norm;

    ModelML2D();
    ModelML2D(int n_ref);

    void initData();
    void setNRef(int n_ref);
    void combineModel(ModelML2D model, int sign);
    void addModel(ModelML2D model);
    void substractModel(ModelML2D model);

    double getSumw(int refno) const;
    double getSumwMirror(int refno) const;
    double getSumwsc(int refno) const;
    MultidimArray<double> getWsumMref(int refno) const;
    double getSumwAllrefs() const;
    double getWsumSigmaOffset() const;
    double getWsumSigmaNoise() const;
    double getSumfracweight() const;
    void updateSigmaOffset(double wsum_sigma_offset);
    void updateSigmaNoise(double wsum_sigma_noise);
    void updateAvePmax(double sumfracweight);
    void updateFractions(int refno, double sumw, double sumw_mirror, double sumw_allrefs);
    void updateScale(int refno, double sumwsc, double sumw);
    ///Just for debugging now
    void print() const;
}
;//close class ModelML2D




/**@defgroup MLalign2D ml_align2d (Maximum likelihood in 2D)
   @ingroup ReconsLibrary */
//@{
/** MLalign2D parameters. */
class ML2DBaseProgram: public XmippProgram
{
public:
    /** Filenames reference selfile/image, fraction docfile & output rootname */
    FileName fn_img, fn_ref, fn_root, fn_frac, fn_sig, fn_doc, fn_oext, fn_scratch, fn_control;
    /** Command line */
    String cline;
    //double sigma_noise2;
    /** Flag for checking mirror images of all references */
    bool do_mirror;
    /** Flag whether to fix estimates for model fractions */
    bool fix_fractions;
    /** Flag whether to fix estimate for sigma of origin offset */
    bool fix_sigma_offset;
    /** Flag whether to fix estimate for sigma of noise */
    bool fix_sigma_noise;
    /** Starting iteration */
    int istart;
    /** Current iteration */
    int iter;
    /** Number of iterations to be performed */
    int Niter;
    /** dimension of the images */
    int dim, dim2, hdim;
    double ddim2;
    /** Number of steps to sample in-plane rotation in 90 degrees */
    int nr_psi;
    /** Number of operations in "flip-array" (depending on do_mirror) */
    int nr_flip;
    /** Sampling rate for in-plane rotation */
    double psi_step;
    /** Total degrees in FOR_ALL_ROTATIONS */
    double psi_max;
    /** Total number of no-mirror rotations in FOR_ALL_FLIPS */
    int nr_nomirror_flips;
    /** Total number of experimental images */
    int nr_images_global;
    /** Total number of local mpi images */
    int nr_images_local;
    /** First and last images, useful for mpi*/
    int myFirstImg, myLastImg;
    /** Stopping criterium */
    double eps;
    /** MetaData files for experimental and reference images */
    MetaData MDimg, MDref, MDlog;
    /** vector for flipping (i.e. 90/180-degree rotations) matrices */
    std::vector<Matrix2D<double> > F;
    /** Vector for images to hold references (new & old) */
    std::vector < Image<double> > Iold;
    /** Matrices for calculating PDF of (in-plane) translations */
    MultidimArray<double> P_phi, Mr2;
    /** Fast mode */
    bool fast_mode;
    /** Fast mode */
    double C_fast;
    /** Offsets for limited translations */
    std::vector<Matrix1D<double> > Vtrans;
    /** Start all optimal offsets from zero values */
    bool zero_offsets;
    /** Limit orientational searches */
    bool limit_rot;
    /** Limited search range for projection directions */
    double search_rot;
    /** Save memory options */
    bool save_mem1, save_mem2, save_mem3;
    /** Vectors to store old phi and theta for all images */
    std::vector<double> imgs_oldphi, imgs_oldtheta;
    /** Flag for using ML3D */
    bool do_ML3D;
    /** Flag for generation of initial models from random subsets */
    bool do_generate_refs;
    /** Vector to store optimal origin offsets (if not written to disc) */
    std::vector<std::vector<double> > imgs_offsets;
    /** For initial guess of mindiff */
    double trymindiff_factor;
    /** Degrees of freedom for the t-student distribution */
    double df, df2, dfsigma2;
    /// Re-normalize internally
    /** Flag to refine normalization of each experimental image */
    bool do_norm;
    /** Grey-scale correction values */
    std::vector<double> imgs_scale, imgs_bgmean, imgs_trymindiff;
    /** Optimal refno from previous iteration */
    std::vector<int> imgs_optrefno;
    /** Overall average scale (to be forced to one)*/
    double average_scale;
    /** Number of (2D/3D) references to be generated */
    int factor_nref;
    /** Number of references per class, usefull for 3D */
    int refs_per_class;
    /** Store convergence */
    std::vector<double> conv;

    /** Model */
    ModelML2D model, *current_model;
    //Some incremental stuff
    //Number of blocks for IEM
    int blocks;
    //Current processing block
    int current_block;

    /** debug flag and seed for randomization */
    int debug, seed;
    //Vector of image IDs in the MetaData object (change order for randomize)
    std::vector<size_t> img_id;
    /** MultidimArray for mpi passing of docfiledata */
    MultidimArray<double> docfiledata;
    /** Flag for restart */
    bool do_restart;

    /**Some flags to params definitions */
    bool referenceExclusive, allowFastOption, allowThreads, allowIEM, allowRestart;
    String defaultRoot;
    int defaultNiter, defaultStartingIter;

    /** Set sampling stuff; flipping matrices, psi_step etc.
     * Also create 0, 90, 180 & 270 degree flipping, as well as mirror
     */
    void initSamplingStuff();

public:
    /* Constructor for some initializations */
    ML2DBaseProgram();
    ///Try to merge produceSideInfo1 and 2
    virtual void produceSideInfo() = 0;
    ///Try to merge produceSideInfo1 and 2
    virtual void produceSideInfo2() = 0;

    /* This function will perform an ML iteration
     * usually composed by 'expectation' and 'maximization'
     */
    virtual void iteration() = 0;

    /// Integrate over all experimental images
    virtual void expectation() = 0;

    /// Update all model parameters, adapted for IEM blocks use
    virtual void maximization() = 0;

    /// Set the number of images, this function is useful only for MPI
    virtual void setNumberOfLocalImages();

    /// Randomize initial images order, only once
    virtual void randomizeImagesOrder();

    /// Create working threads
    virtual void createThreads(){};//by default do nothing

    /// Exit threads and free memory
    virtual void destroyThreads(){};//by default do nothing

    ///Write output files
    virtual void writeOutputFiles(const ModelML2D &model, OutputType outputType = OUT_FINAL) = 0;


    virtual bool checkConvergence();

    /// Add docfiledata to docfile
    virtual void addPartialDocfileData(const MultidimArray<double> &data, int first, int last) = 0;

    ///Main function of the program
    virtual void run();

    /// Divide the definition of params in several
    ///functions, also allowing other programs
    ///to include the ML2D params definition
    void defineBasicParams(XmippProgram * prog);
    void defineAdditionalParams(XmippProgram * prog, const char * sectionLine);
    void defineHiddenParams(XmippProgram *prog);

};//end of class ML2DBaseProgram



//@}
#endif
