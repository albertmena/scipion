/***************************************************************************
 * Authors:     Joaquin Oton (joton@cnb.csic.es)
 *
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

#ifndef IMAGE_BASE_H_
#define IMAGE_BASE_H_

#include <typeinfo>
#include <fcntl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "funcs.h"
#include "memory.h"
#include "multidim_array.h"
#include "transformations.h"
#include "metadata.h"
#include "datatype.h"

// Includes for rwTIFF which cannot be inside it
#include <cstring>
#include "../../external/tiff-3.9.4/libtiff/tiffio.h"

/* Minimum size of a TIFF file to be mapped to a tempfile in case of mapping from
 * image file is required
 */
const size_t tiff_map_min_size = 200e6;

/// @defgroup Images Images
/// @ingroup DataLibrary

//@{
/** Transform type.
 *  This type defines the kind of image.
 */
typedef enum
{
    NoTransform = 0,        // No transform
    Standard = 1,           // Standard transform: origin = (0,0,0)
    Centered = 2,           // Centered transform: origin = (nx/2,ny/2,nz/2)
    Hermitian = 3,          // Hermitian half: origin = (0,0,0)
    CentHerm = 4            // Centered hermitian: origin = (0,ny/2,nz/2)
} TransformType;

/** Write mode
 * This class defines the writing behavior.
 */
typedef enum
{
    WRITE_OVERWRITE, //forget about the old file and overwrite it
    WRITE_APPEND,    //append and object at the end of a stack, so far can not append stacks
    WRITE_REPLACE,   //replace a particular object by another
    WRITE_READONLY   //only can read the file
} WriteMode;

/* Cast Write mode
 * This enum defines the cast writing behavior
 */
typedef enum
{
    CAST,       //Only cast the data type
    CONVERT,    //Convert the data from one type to another
    ADJUST      //Adjust the histogram to fill the gray level range
} CastWriteMode;

/** Open File struct
 * This struct is used to share the File handlers with Image Collection class
 */
struct ImageFHandler
{
    FILE*     fimg;       // Image File handler
    FILE*     fhed;       // Image File header handler
    TIFF*     tif;        // TIFF Image file hander
    FileName  fileName;   // Image file name
    FileName  headName;   // Header file name
    FileName  ext_name;   // Filename extension
    bool     exist;       // Shows if the file exists. Equal 0 means file does not exist or not stack.
};


/// @name ImagesSpeedUp Images Speed-up
/// @{

/** Volume Matrix access.
 *
 * This macro does the same as the normal 3D matrix access but in a faster way
 * as no function call is generated.
 *
 * @code
 * VOLMATRIX(V).resize(128, 128, 128);
 *
 * VOLMATRIX(V2) = VOLMATRIX(V1) + VOLMATRIX(V2);
 * @endcode
 */
#define VOLMATRIX(V) ((V).data)

/** Image Matrix access.
 *
 * This macro does the same as the normal 2D matrix access but in a faster way
 * as no function call is generated.
 *
 * @code
 * IMGMATRIX(V).resize(128, 128);
 *
 * IMGMATRIX(V2) = IMGMATRIX(V1) + IMGMATRIX(V2);
 * @endcode
 */
#define IMGMATRIX(I) ((I).data)

/** Pixel access.
 * For fast access to pixel values (and for backwards compatibility of the code)
 */
#define IMGPIXEL(I, i, j) A2D_ELEM(((I).data), (i), (j))

/** Physical pixel access.
 *
 * The physical pixel access gives you access to a pixel by its physical
 * position and not by its logical one. This access shouldn't be used as a
 * custom, use instead the logical access, but there might be cases in which
 * this access might be interesting. Physical positions start at index 0 in C.
 *
 * @code
 * std::cout << "This is the first pixel stored in the Image " <<
 *     DIRECT_IMGPIXEL(V, 0, 0) << std::endl;
 * @endcode
 */
#define DIRECT_IMGPIXEL(I, i, j) DIRECT_A2D_ELEM(((I).data), (i), (j))

/** Voxel access.
 *
 * This macro does the same as the normal voxel access (remember, logical
 * access) but in a faster way as no function call is generated.
 *
 * @code
 * std::cout << "Grey level of voxel (2,-3,-3) of the Volume = " <<
 *     VOLVOXEL(V, 2, -3, -3) << std::endl;
 *
 * VOLVOXEL(I, 2, -3, -3) = VOLVOXEL(I, 2, -3, -2);
 * @endcode
 */
#define VOLVOXEL(V, k, i, j) A3D_ELEM(((V).data), (k), (i), (j))

/** Physical voxel access.
 *
 * The physical voxel access gives you access to a voxel by its physical
 * position and not by its logical one. This access shouldn't be used as a
 * custom, use instead the logical access, but there might be cases in which
 * this access might be interesting. Physical positions start at index 0 in C.
 *
 * @code
 * std::cout << "This is the first voxel stored in the Volume " <<
 *     DIRECT_VOLVOXEL(V, 0, 0, 0) << std::endl;
 * @endcode
 */
#define DIRECT_VOLVOXEL(I, k, i, j) DIRECT_A3D_ELEM(((I).data), (k), (i), (j))
//@}

/** Swapping trigger.
 * Threshold file z size above which bytes are swapped.
 */
#define SWAPTRIG     65535


// Image base class
class ImageBase
{
public:
    std::vector<MDRow>  MD;                     // data for each subimage
    MDRow               MDMainHeader;           // data for the file

protected:
    FileName            filename;    // File name
    FileName            dataFName;   // Data File name without flags
    FILE*                fimg;        // Image File handler
    FILE*                fhed;        // Image File header handler
    TIFF*                tif;         // TIFF Image file hander
    bool                stayOpen;    // To maintain the image file open after read/write
    int                 dataflag;    // Flag to force reading of the data
    unsigned long       i;           // Current image number (may be > NSIZE)
    size_t       offset;      // Data offset
    int                 swap;        // Perform byte swapping upon reading
    TransformType       transform;   // Transform type
    int                 replaceNsize;// Stack size in the replace case
    bool                 _exists;     // does target file exists?
    // equal 0 is not exists or not a stack
    bool                mmapOnRead;  // Mapping when reading from file
    bool                mmapOnWrite; // Mapping when writing to file
    int                 mFd;         // Handle the file in reading method and mmap
    size_t              mappedSize;  // Size of the mapped file
    size_t              mappedOffset;// Offset for the mapped file

public:

    /** Init.
     * Initialize everything to 0*/
    void init();

    /** Clear.
     * Initialize everything to 0*/
    virtual void clear()=0;

    /** Clear the header of the image*/
    void clearHeader();

    /** Check whether image is complex based on T*/
    virtual bool isComplexT() const=0;

    /** Check whether image is complex based on transform*/
    bool isComplex() const
    {
        return !(transform==NoTransform);
    }

    /** Destructor.*/
    ~ImageBase()
    {}

    /** Is this file an image
     *
     *  Check whether a real-space image can be read*/
    bool isImage(const FileName &name)
    {
        return !read(name, false);
    }

    /** Is this file a real-valued image
     *
     *  Check whether a real-space image can be read
     */
    bool isRealImage(const FileName &name)
    {
        return (isImage(name) && !isComplex());
    }

    /** Is this file a complex image
     *
     *  Check whether a fourier-space (complex) image can be read
     */
    bool isComplexImage(const FileName &name)
    {
        return (isImage(name) && isComplex());
    }

    /** Rename the image*/
    void rename (const FileName &name)
    {
        filename = name;
    }

    /** Create a mapped image file
     *
     * An image file, which name and format are given by filename,
     * is created with the given size. Then the image is mapped to this file.
     *
     * @code
     * Image I(64,64,1,1,"image.spi");
     * @endcode
     */
    virtual void newMappedFile(int Xdim, int Ydim, int Zdim, int Ndim, const FileName _filename)=0;

    /** General read function
     * you can read a single image from a single image file
     * or a single image file from an stack, in the second case
     * the select slide may come in the image name or in the select_img parameter
     * file name takes precedence over select_img
     * If -1 is given the whole object is read
     *
     * This function cannot apply geometrical transformations, but can map the image in disk
     */
    int read(const FileName &name, bool readdata=true, int select_img = -1,
             bool mapData = false);

    /** General read function
     * you can read a single image from a single image file
     * or a single image file from an stack, in the second case
     * the select slide may come in the image name or in the select_img parameter
     * file name takes precedence over select_img
     * If -1 is given the whole object is read
     *
     * This function can apply geometrical transformations, but cannot map the image in disk
     */
    int readApplyGeo(const FileName &name, bool readdata=true, int select_img = -1,
             bool only_apply_shifts = false, MDRow * row = NULL);

    /** Read an image from metadata, filename is provided*/
    int readApplyGeo(const FileName &name, const MetaData &md, size_t objId,
             bool readdata=true, int select_img = -1,
             bool only_apply_shifts = false);

    /** Read an image from metadata, filename is taken from MDL_IMAGE */
    int readApplyGeo(const MetaData &md, size_t objId,
             bool readdata=true, int select_img = -1,
             bool only_apply_shifts = false);

    /* Read an image with a lower resolution as a preview image.
     * If Zdim parameter is not passed, then all slices are rescaled.
     */
    virtual int readPreview(const FileName &name, int Xdim, int Ydim, int Zdim = -1, int select_img = 0)=0;

    /** General write function
     * select_img= which slice should I replace
     * overwrite = 0, append slice
     * overwrite = 1 overwrite slice
     */
    void write(const FileName &name="", int select_img=-1, bool isStack=false,
               int mode=WRITE_OVERWRITE,bool adjust=false);

    /** Check file Datatype is same as T type to use mmap.
     */
    virtual bool checkMmapT(DataType datatype)=0;

    /** Write an entire page as datatype
     *
     * A page of datasize_n elements T is cast to datatype and written to fimg
     * The memory for the casted page is allocated and freed internally.
     */
    virtual void writePageAsDatatype(FILE * fimg, DataType datatype, size_t datasize_n )=0;

    /** Swap an entire page
      * input pointer char *
      */
    void swapPage(char * page, size_t pageNrElements, DataType datatype);

    /** Get file name
     *
     * @code
     * std::cout << "Image name = " << I.name() << std::endl;
     * @endcode
     */
    const FileName & name() const
    {
        return filename;
    }

    /** Get Image dimensions
     */
    virtual void getDimensions(int &Xdim, int &Ydim, int &Zdim, unsigned long &Ndim) const=0;

    /** Get whole number of pixels
     */
    virtual long unsigned int getSize() const=0;

    /** Get Image offset and swap
     */
    void getOffsetAndSwap(size_t &_offset, int &_swap) const
    {
        _offset = offset;
        _swap = swap;
    }

    /* Is there label in the individual header
    */
    bool individualContainsLabel(MDLabel label) const
    {
        return (!MD.empty() && MD[0].containsLabel(label));
    }

    /* Is there label in the main header */
    bool mainContainsLabel(MDLabel label) const
    {
        return MDMainHeader.containsLabel(label);
    }

    /** Get Rot angle
    *
    * @code
    * std::cout << "First Euler angle " << I.rot() << std::endl;
    * @endcode
    */
    double rot(const long int n = 0) const;

    /** Get Tilt angle
     *
     * @code
     * std::cout << "Second Euler angle " << I.tilt() << std::endl;
     * @endcode
     */
    double tilt(const long int n = 0) const;

    /** Get Psi angle
     *
     * @code
     * std::cout << "Third Euler angle " << I.psi() << std::endl;
     * @endcode
     */
    double psi(const long int n = 0) const;

    /** Get Xoff
     *
     * @code
     * std::cout << "Origin offset in X " << I.Xoff() << std::endl;
     * @endcode
     */
    double Xoff(const long int n = 0) const;

    /** Get Yoff
     *
     * @code
     * std::cout << "Origin offset in Y " << I.Yoff() << std::endl;
     * @endcode
     */
    double Yoff(const long int n = 0) const;

    /** Get Zoff
     *
     * @code
     * std::cout << "Origin offset in Z " << I.Zoff() << std::endl;
     * @endcode
     */
    double Zoff(const long int n = 0) const;

    /** Get Weight
    *
    * @code
    * std::cout << "weight= " << I.weight() << std::endl;
    * @endcode
    */
    double weight(const long int n = 0) const;

    /** Get Scale factor
    *
    * @code
    * std::cout << "scale= " << I.scale() << std::endl;
    * @endcode
    */
    double scale(const long int n = 0) const;

    /** Get Flip
    *
    * @code
    * std::cout << "flip= " << flip() << std::endl;
    * @endcode
    */
    bool flip(const long int n = 0) const;

    /** Data type
        *
        * @code
        * std::cout << "datatype= " << dataType() << std::endl;
        * @endcode
        */
    DataType dataType() const;

    /** Sampling RateX
    *
    * @code
    * std::cout << "sampling= " << samplingRateX() << std::endl;
    * @endcode
    */
    double samplingRateX() const;

    virtual void setDimensions(int Xdim, int Ydim, int Zdim, unsigned long Ndim)=0;

    /** Set file name
     */
    void setName(const FileName &_filename)
    {
        filename = _filename;
    }

    /** Set Euler angles in image header
     */
    void setEulerAngles(double rot, double tilt, double psi,
                        long int n = 0);

    /** Get Euler angles from image header
     */
    void getEulerAngles(double &rot, double &tilt, double &psi,
                        long int n = 0);

    /** Set Rotation angle to image */
    void setRot(double rot, long int n = 0)
    {
        MD[n].setValue(MDL_ANGLEROT, rot);
    }

    /** Set Tilt angle to image */
    void setTilt(double tilt, long int n = 0)
    {
        MD[n].setValue(MDL_ANGLETILT, tilt);
    }

    /** Set Rotation angle to image */
    void setPsi(double psi, long int n = 0)
    {
        MD[n].setValue(MDL_ANGLEPSI, psi);
    }

    /** Set origin offsets in image header
     */
    void setShifts(double xoff, double yoff, double zoff = 0.,
                   long int n = 0);

    /** Get origin offsets from image header
      */
    void getShifts(double &xoff, double &yoff, double &zoff,
                   long int n = 0) const;

    /** Set X offset in image header
     */
    void setXoff(double xoff, long int n = 0)
    {
        MD[n].setValue(MDL_ORIGINX, xoff);
    }

    /** Set Y offset in image header
     */
    void setYoff(double yoff, long int n = 0)
    {
        MD[n].setValue(MDL_ORIGINY, yoff);
    }

    /** Set Z offset in image header
     */
    void setZoff(double zoff, long int n = 0)
    {
        MD[n].setValue(MDL_ORIGINZ, zoff);
    }

    /** Set scale in image header
     */
    void setScale(double scale, long int n = 0)
    {
        MD[n].setValue(MDL_SCALE, scale);
    }

    /** Get scale from image header
     */
    void getScale(double &scale, long int n = 0)
    {
        MD[n].getValue(MDL_SCALE, scale);
    }

    /** Set flip in image header
     */
    void setFlip(bool flip, long int n = 0)
    {
        MD[n].setValue(MDL_FLIP, flip);
    }

    /** Set Weight in image header
    */
    void setWeight(double weight, long int n = 0)
    {
        MD[n].setValue(MDL_WEIGHT, weight);
    }

    /** Get geometric transformation matrix from 2D-image header
      */
    virtual void getTransformationMatrix(Matrix2D<double> &A,
                                         bool only_apply_shifts = false,
                                         long int n = 0)=0;

    /** Sum this object with other file and keep in this object
      */
    virtual void sumWithFile(const FileName &fn)=0;


protected:

    /**
     *  Specific read functions for different file formats
     */
#include "rwDM3.h"
#include "rwIMAGIC.h"
#include "rwMRC.h"
#include "rwINF.h"
#include "rwRAW.h"
#include "rwSPIDER.h"
#include "rwSPE.h"
#include "rwTIA.h"
    //#include "rwTIFF.h"


    /** Open file function
      * Open the image file and returns its file hander.
      */
    ImageFHandler* openFile(const FileName &name, int mode = WRITE_READONLY) const;

    /** Close file function.
      * Close the image file according to its name and file handler.
      */
    void closeFile(ImageFHandler* hFile = NULL);

    /* Internal read image file method.
     */
    virtual int _read(const FileName &name, ImageFHandler* hFile, bool readdata=true, int select_img = -1,
                      bool apply_geo = false, bool only_apply_shifts = false,
                      MDRow * row = NULL, bool mapData = false)=0;

    /* Internal write image file method.
     */
    virtual void _write(const FileName &name, ImageFHandler* hFile, int select_img=-1,
                        bool isStack=false, int mode=WRITE_OVERWRITE, bool adjust=false)=0;

    /** Read the raw data
      */
    virtual void readData(FILE* fimg, int select_img, DataType datatype, unsigned long pad)=0;

    /* Write the raw date after a data type casting.
     */
    virtual void writeData(FILE* fimg, size_t offset, DataType wDType, size_t datasize_n,
                           CastWriteMode castMode=CAST)=0;

    /* Mmap the Image class to an image file.
     */
    virtual void mmapFile()=0;

    /* Munmap the image file.
     */
    virtual void munmapFile()=0;

    /* Return the datatype of the current image object
     */
    virtual DataType myT()=0;

};

#endif /* IMAGE_BASE_H_ */
