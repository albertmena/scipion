/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package browser.windows;

import browser.LABELS;
import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.Roi;
import ij.gui.Toolbar;
import ij.process.StackConverter;
import ij3d.Content;
import ij3d.Image3DUniverse;
import java.awt.BorderLayout;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 *
 * @author juanjo
 */
public class XmippMenuBar extends MenuBar implements ActionListener {

    private final static int UNIVERSE_W = 400, UNIVERSE_H = 400;
    private ImagePlus imp;
    // *** Transform ***
    private Menu menuTransform = new Menu(LABELS.OPERATION_MENU_TRANSFORM);
    private Menu menuFlip = new Menu(LABELS.OPERATION_MENU_FLIP);
    private MenuItem flipV = new MenuItem(LABELS.OPERATION_FLIP_VERTICAL);
    private MenuItem flipH = new MenuItem(LABELS.OPERATION_FLIP_HORIZONTAL);
    private Menu menuRotate = new Menu(LABELS.OPERATION_MENU_ROTATE);
    private MenuItem rotateL = new MenuItem(LABELS.OPERATION_ROTATE_LEFT);
    private MenuItem rotateR = new MenuItem(LABELS.OPERATION_ROTATE_RIGHT);
    private Menu menuReslice = new Menu(LABELS.OPERATION_MENU_RESLICE);
    private MenuItem resliceTop = new MenuItem(LABELS.OPERATION_RESLICE_TOP);
    private MenuItem resliceRight = new MenuItem(LABELS.OPERATION_RESLICE_RIGHT);
    // *** Denoising ***
    private Menu menuDenoising = new Menu(LABELS.OPERATION_MENU_DENOISING);
    private MenuItem itemFFT_band_pass_filter = new MenuItem(LABELS.OPERATION_FFT_BAND_PASS_FILTER);
    private MenuItem itemAnisotropicDiffusion = new MenuItem("Anisotropic Diffusion (edge-preserving noise reduction)");
    // *** Open with ***
    private Menu menuOpenWith = new Menu(LABELS.OPERATION_MENU_OPEN_WITH);
    private MenuItem item3DViewer = new MenuItem("3D Viewer");
    private MenuItem itemVolumeViewer3DSlicer = new MenuItem("Volume Viewer/3D-Slicer");
    private MenuItem itemVolumeJ = new MenuItem("VolumeJ");
    // *** Info ***
    private Menu menuInfo = new Menu(LABELS.OPERATION_MENU_INFO);
    private MenuItem itemGoToSlice = new MenuItem(LABELS.LABEL_GO_TO_SLICE);
    private MenuItem itemHistogram = new MenuItem(LABELS.OPERATION_HISTOGRAM);
    private MenuItem itemPlotProfile = new MenuItem(LABELS.OPERATION_PLOT_PROFILE);
    private MenuItem itemMeasurements = new MenuItem(LABELS.OPERATION_MEASUREMENTS);
    private MenuItem itemAutocorrelation = new MenuItem("Autocorrelation");
    private MenuItem itemConcentricCircles = new MenuItem("Concentric Circles (non-destructive overlay)");
    private MenuItem itemLineAnalyzer = new MenuItem("Line Analyzer");
    private MenuItem itemOvalProfilePlot = new MenuItem("Oval Profile Plot");
    private MenuItem itemRadialProfilePlotAngle = new MenuItem("Radial Profile Plot Angle");
    private MenuItem itemRadialProfilePlotHeight = new MenuItem("Radial Profile Plot Height");
    // *** Thresholding ***
    private Menu menuThresholding = new Menu(LABELS.OPERATION_MENU_THRESHOLDING);
    private MenuItem itemThreshold = new MenuItem(LABELS.OPERATION_THRESHOLD);
    private MenuItem itemOtsuThresholding = new MenuItem("Otsu Thresholding");
    private MenuItem itemMultiOtsuThreshold = new MenuItem("Multi Otsu Threshold");
    // *** Binary ***
    private Menu menuBinary = new Menu(LABELS.OPERATION_MENU_BINARY);
    private MenuItem itemErode = new MenuItem("Erode");
    private MenuItem itemDilate = new MenuItem("Dilate");
    private MenuItem itemOpen = new MenuItem("Open");
    private MenuItem itemClose = new MenuItem("Close");
    private MenuItem itemOutline = new MenuItem("Outline");
    private MenuItem itemFillHoles = new MenuItem("Fill holes");
    private MenuItem itemSkeletonize = new MenuItem("Skeletonize");
    private MenuItem itemDistanceMap = new MenuItem("Distance map");
    private MenuItem itemUltimatePoints = new MenuItem("Ultimate points");
    private MenuItem itemWatershed = new MenuItem("Watershed");
    private MenuItem itemVoronoi = new MenuItem("Voronoi");
    private MenuItem itemOptions = new MenuItem("Options");
    // *** *** ***
    private Menu menuPREVIOUS = new Menu("[PREVIOUS]");
    private Menu menuProcess = new Menu(LABELS.OPERATION_MENU_PROCESS);
    private MenuItem itemBC = new MenuItem(LABELS.OPERATION_BC);
    private MenuItem itemSubtractBG = new MenuItem(LABELS.OPERATION_SUBTRACTBG);
    private MenuItem itemGaussianBlur = new MenuItem(LABELS.OPERATION_GAUSSIAN_BLUR);
    private MenuItem itemFFT = new MenuItem(LABELS.OPERATION_FFT);
//    private Menu menuGoTo = new Menu(LABELS.OPERATION_MENU_GO_TO);
    private MenuItem openAs3D = new MenuItem(LABELS.OPERATION_OPEN_AS_3D);
    private Menu menuPlugins = new Menu(LABELS.OPERATION_MENU_PLUGINS);
    private Menu menuAnalysis = new Menu(LABELS.OPERATION_MENU_ANALYSIS);
    private MenuItem itemSyncMeasure3D = new MenuItem("Sync Measure 3D");
    private MenuItem itemTemplateMatching = new MenuItem("Template Matching");
    private Menu menuConvert = new Menu(LABELS.OPERATION_MENU_CONVERT);
    private MenuItem itemFloatMorphology = new MenuItem("Float Morphology");
    private MenuItem itemMeanShiftFilter = new MenuItem("Mean Shift Filter (edge-preserving smoothing)");
    private MenuItem itemCLAHE = new MenuItem("CLAHE (Contrast Limited Adaptive Histogram Equalization)");
    private Menu menuThreshold = new Menu(LABELS.OPERATION_MENU_THRESHOLD);
    private MenuItem itemMixtureModelingThresholding = new MenuItem("Mixture Modeling Thresholding");
    private MenuItem itemMaximumEntropyThresholding = new MenuItem("Maximum Entropy Thresholding");
    private MenuItem itemMultiThresholder = new MenuItem("MultiThresholder");
    private MenuItem itemSIOX = new MenuItem("SIOX (Simple Interactive Object Extraction)");
    private MenuItem itemRATS = new MenuItem("RATS (Robust Automatic Threshold Selection)");
    private Menu menuOther = new Menu(LABELS.OPERATION_MENU_OTHER);
    private MenuItem itemContourPlotter = new MenuItem("Contour Plotter");
    private MenuItem itemDottedandDashedLines = new MenuItem("Dotted and Dashed Lines");
    private MenuItem itemRadialGrid = new MenuItem("Radial Grid");
    private MenuItem itemPolarTransformer = new MenuItem("Polar Transformer (convert to polar coordinates)");
    private MenuItem itemVoxelCounter = new MenuItem("Voxel Counter");
    private MenuItem itemSubstackMaker = new MenuItem("Substack Maker");
    private MenuItem itemRadialReslice = new MenuItem("Radial Reslice (orthogonal reconstructions)");
    private MenuItem itemStackSlicer = new MenuItem("StackSlicer (dynamic orthoganal views)");
    private MenuItem itemUntiltStack = new MenuItem("Untilt Stack (removes tilt from a stack of images)");
    private MenuItem itemStraightenCurvedObjects = new MenuItem("Straighten Curved Objects");
    private MenuItem itemSyncWindows = new MenuItem("Sync Windows");
    private MenuItem itemFlowJ = new MenuItem("FlowJ");
    private MenuItem itemFlow3J = new MenuItem("Flow3J");
    private MenuItem itemSurfaceJ = new MenuItem("SurfaceJ");
    private MenuItem itemPCA = new MenuItem("PCA (Principal Component Analysis)");
    private MenuItem itemTransformJ = new MenuItem("TransformJ");
    private MenuItem itemFeatureJ = new MenuItem("FeatureJ");
    private MenuItem itemObjectJ = new MenuItem("ObjectJ");

    public XmippMenuBar(ImagePlus imp) {
        super();

        this.imp = imp;

        createMenuBar();

        // Enables / disables depending on context (image or stack)
        menuReslice.setEnabled(imp.getStackSize() > 1);
        itemGoToSlice.setEnabled(imp.getStackSize() > 1);
    }

    private void createMenuBar() {
        // Transform ***
        menuTransform.add(menuFlip);
        menuFlip.add(flipV);
        menuFlip.add(flipH);
        flipV.addActionListener(this);
        flipH.addActionListener(this);

        menuTransform.add(menuRotate);
        menuRotate.add(rotateL);
        menuRotate.add(rotateR);
        rotateL.addActionListener(this);
        rotateR.addActionListener(this);

        menuTransform.add(menuReslice);
        menuReslice.add(resliceTop);
        menuReslice.add(resliceRight);
        resliceTop.addActionListener(this);
        resliceRight.addActionListener(this);

        // Denoising ***
        menuDenoising.add(itemFFT_band_pass_filter);
        menuDenoising.add(itemAnisotropicDiffusion);
        itemFFT_band_pass_filter.addActionListener(this);
        itemAnisotropicDiffusion.addActionListener(this);

        // Open with ***
        menuOpenWith.add(item3DViewer);
        menuOpenWith.add(itemVolumeViewer3DSlicer);
        menuOpenWith.add(itemVolumeJ);
        item3DViewer.addActionListener(this);
        itemVolumeViewer3DSlicer.addActionListener(this);
        itemVolumeJ.addActionListener(this);

        // Info ***
        menuInfo.add(itemGoToSlice);
        menuInfo.addSeparator();
        menuInfo.add(itemHistogram);
        menuInfo.add(itemPlotProfile);
        menuInfo.add(itemMeasurements);
        menuInfo.add(itemAutocorrelation);
        menuInfo.add(itemConcentricCircles);
        menuInfo.add(itemLineAnalyzer);
        menuInfo.add(itemOvalProfilePlot);
        menuInfo.add(itemRadialProfilePlotAngle);
        menuInfo.add(itemRadialProfilePlotHeight);

        itemGoToSlice.addActionListener(this);
        itemHistogram.addActionListener(this);
        itemPlotProfile.addActionListener(this);
        itemMeasurements.addActionListener(this);
        itemAutocorrelation.addActionListener(this);
        itemConcentricCircles.addActionListener(this);
        itemLineAnalyzer.addActionListener(this);
        itemOvalProfilePlot.addActionListener(this);
        itemRadialProfilePlotAngle.addActionListener(this);
        itemRadialProfilePlotHeight.addActionListener(this);

        // Thresholding ***
        menuThresholding.add(itemThreshold);
        menuThresholding.add(itemOtsuThresholding);
        menuThresholding.add(itemMultiOtsuThreshold);

        itemThreshold.addActionListener(this);
        itemOtsuThresholding.addActionListener(this);
        itemMultiOtsuThreshold.addActionListener(this);

        // Binary ***
        menuBinary.add(itemErode);
        menuBinary.add(itemDilate);
        menuBinary.add(itemOpen);
        menuBinary.add(itemClose);
        menuBinary.addSeparator();
        menuBinary.add(itemOutline);
        menuBinary.add(itemFillHoles);
        menuBinary.add(itemSkeletonize);
        menuBinary.addSeparator();
        menuBinary.add(itemDistanceMap);
        menuBinary.add(itemUltimatePoints);
        menuBinary.add(itemWatershed);
        menuBinary.add(itemVoronoi);
        menuBinary.addSeparator();
        menuBinary.add(itemOptions);

        itemErode.addActionListener(this);
        itemDilate.addActionListener(this);
        itemOpen.addActionListener(this);
        itemClose.addActionListener(this);
        itemOutline.addActionListener(this);
        itemFillHoles.addActionListener(this);
        itemSkeletonize.addActionListener(this);
        itemDistanceMap.addActionListener(this);
        itemUltimatePoints.addActionListener(this);
        itemWatershed.addActionListener(this);
        itemVoronoi.addActionListener(this);
        itemOptions.addActionListener(this);

        // *** *** *** ***
        // PREVIOUS MENUS
        // *** *** *** ***
        menuPREVIOUS.add(menuProcess);

        // Process.
        menuProcess.add(itemBC);
        menuProcess.add(itemSubtractBG);
        menuProcess.add(itemGaussianBlur);
        menuProcess.add(itemFFT);

        itemBC.addActionListener(this);
        itemSubtractBG.addActionListener(this);
        itemGaussianBlur.addActionListener(this);
        itemFFT.addActionListener(this);

        // Plugins
        menuPlugins.add(menuAnalysis);
        menuAnalysis.add(itemSyncMeasure3D);
        menuAnalysis.add(itemTemplateMatching);

        menuPlugins.add(menuConvert);
        menuConvert.add(itemCLAHE);
        menuConvert.add(itemFloatMorphology);
        menuConvert.add(itemMeanShiftFilter);

        menuPlugins.add(menuThreshold);
        menuThreshold.add(itemMaximumEntropyThresholding);
        menuThreshold.add(itemMixtureModelingThresholding);
        menuThreshold.add(itemMultiThresholder);
        menuThreshold.add(itemRATS);
        menuThreshold.add(itemSIOX);
        menuThreshold.add(itemWatershed);

        menuPlugins.add(menuOther);
        menuOther.add(itemContourPlotter);
        menuOther.add(itemDottedandDashedLines);
        menuOther.add(itemFeatureJ);
        menuOther.add(itemFlowJ);
        menuOther.add(itemFlow3J);
        menuOther.add(itemObjectJ);
        menuOther.add(itemPCA);
        menuOther.add(itemPolarTransformer);
        menuOther.add(itemRadialGrid);
        menuOther.add(itemRadialReslice);
        menuOther.add(itemStackSlicer);
        menuOther.add(itemStraightenCurvedObjects);
        menuOther.add(itemSubstackMaker);
        menuOther.add(itemSurfaceJ);
        menuOther.add(itemSyncWindows);
        menuOther.add(itemTransformJ);
        menuOther.add(itemUntiltStack);
        menuOther.add(itemVoxelCounter);

        // Action listeners
        itemAutocorrelation.addActionListener(this);
        itemLineAnalyzer.addActionListener(this);
        itemOvalProfilePlot.addActionListener(this);
        itemRadialProfilePlotAngle.addActionListener(this);
        itemRadialProfilePlotHeight.addActionListener(this);
        itemSyncMeasure3D.addActionListener(this);
        itemTemplateMatching.addActionListener(this);
        itemConcentricCircles.addActionListener(this);
        itemAnisotropicDiffusion.addActionListener(this);

        itemFloatMorphology.addActionListener(this);
        itemMeanShiftFilter.addActionListener(this);
        itemCLAHE.addActionListener(this);

        itemMixtureModelingThresholding.addActionListener(this);
        itemWatershed.addActionListener(this);
        itemMaximumEntropyThresholding.addActionListener(this);
        itemMultiThresholder.addActionListener(this);
        itemSIOX.addActionListener(this);
        itemRATS.addActionListener(this);

        itemContourPlotter.addActionListener(this);
        itemDottedandDashedLines.addActionListener(this);
        itemRadialGrid.addActionListener(this);
        itemPolarTransformer.addActionListener(this);
        itemVoxelCounter.addActionListener(this);
        itemSubstackMaker.addActionListener(this);
        itemRadialReslice.addActionListener(this);
        itemStackSlicer.addActionListener(this);
        itemUntiltStack.addActionListener(this);
        itemStraightenCurvedObjects.addActionListener(this);
        itemSyncWindows.addActionListener(this);
        itemVolumeJ.addActionListener(this);
        itemFlowJ.addActionListener(this);
        itemFlow3J.addActionListener(this);
        itemSurfaceJ.addActionListener(this);
        itemPCA.addActionListener(this);
        itemTransformJ.addActionListener(this);
        itemFeatureJ.addActionListener(this);
        itemObjectJ.addActionListener(this);

        // Adds menus.
        add(menuTransform);
        add(menuDenoising);
        add(menuOpenWith);
        add(menuInfo);
        add(menuThresholding);
        add(menuBinary);

        // Items to rearrange.
        add(menuPlugins);
        add(menuPREVIOUS);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == flipV) {
            imp.getProcessor().flipVertical();
        } else if (e.getSource() == flipH) {
            imp.getProcessor().flipHorizontal();
        } else if (e.getSource() == rotateL) {
            IJ.run("Rotate 90 Degrees Left");
        } else if (e.getSource() == rotateR) {
            IJ.run("Rotate 90 Degrees Right");
        } else if (e.getSource() == itemHistogram) {
            IJ.run("Histogram");
        } else if (e.getSource() == itemPlotProfile) {
            // Check if there is a line selected, so , if not, it
            // selects the right tool for the next time.
            Roi roi = imp.getRoi();
            if (roi == null || !roi.isLine()) {
                IJ.setTool(Toolbar.LINE);
            }

            IJ.run("Plot Profile");
        } else if (e.getSource() == itemMeasurements) {
            IJ.run("Set Measurements...");
            IJ.run("Measure");
        } else if (e.getSource() == itemBC) {
            IJ.run("Brightness/Contrast...");
        } else if (e.getSource() == itemThreshold) {
            IJ.run("Threshold...");
        } else if (e.getSource() == itemSubtractBG) {
            IJ.run("Subtract Background...");
        } else if (e.getSource() == itemGaussianBlur) {
            IJ.run("Gaussian Blur...");
        } else if (e.getSource() == itemFFT) {
            IJ.run("FFT");
        } else if (e.getSource() == itemFFT_band_pass_filter) {
            IJ.run("Bandpass Filter...");//, "filter_large=40 filter_small=3 suppress=None tolerance=5 autoscale saturate");
        } else if (e.getSource() == resliceTop) {
            IJ.run("Reslice [/]...", "slice=1.000 start=Top");
        } else if (e.getSource() == resliceRight) {
            IJ.run("Reslice [/]...", "slice=1.000 start=Right");
        } else if (e.getSource() == openAs3D) {
            run3DViewer(imp);
        } else if (e.getSource() == itemGoToSlice) {
            GenericDialog dialog = new GenericDialog(LABELS.TITLE_GO_TO_SLICE);
            dialog.addNumericField("Slice: ", imp.getCurrentSlice(), String.valueOf(imp.getStackSize()).length());
            dialog.showDialog();

            int slice = (int) dialog.getNextNumber();
            if (slice < 1) {
                slice = 1;
            } else if (slice > imp.getStackSize()) {
                slice = imp.getStackSize();
            }

            imp.setSlice(slice);
        } else if (e.getSource() == itemAnisotropicDiffusion) {
            IJ.run("Anisotropic Diffusion...");
        } else if (e.getSource() == itemAutocorrelation) {
            IJ.run("Auto Corr");
        } else if (e.getSource() == itemConcentricCircles) {
            IJ.run("Concentric Circles");
        } else if (e.getSource() == itemLineAnalyzer) {
            IJ.run("Line Analyzer");    // ?
        } else if (e.getSource() == itemOvalProfilePlot) {
            IJ.run("Oval Profile");
        } else if (e.getSource() == itemRadialProfilePlotAngle) {
            IJ.run("Radial Profile Angle");
        } else if (e.getSource() == itemRadialProfilePlotHeight) {
            IJ.run("Radial Profile Height");
        } else if (e.getSource() == itemSyncMeasure3D) {
            IJ.run("Sync Measure 3D");
        } else if (e.getSource() == itemTemplateMatching) {
            IJ.run("Create Template");
        } else if (e.getSource() == itemCLAHE) {
            IJ.run("CLAHE ");
        } else if (e.getSource() == itemFloatMorphology) {
            IJ.run("Float Morphology");
        } else if (e.getSource() == itemMeanShiftFilter) {
            IJ.run("Mean Shift");
        } else if (e.getSource() == itemMaximumEntropyThresholding) {
            IJ.run("Entropy Threshold");
        } else if (e.getSource() == itemMixtureModelingThresholding) {
            IJ.run("Mixture Modeling");
        } else if (e.getSource() == itemMultiThresholder) {
            IJ.run("MultiThresholder");
        } else if (e.getSource() == itemMultiOtsuThreshold) {
            IJ.run("Multi OtsuThreshold");
        } else if (e.getSource() == itemOtsuThresholding) {
            IJ.run("Otsu Thresholding");
        } else if (e.getSource() == itemRATS) {
            IJ.run("RATS ");
        } else if (e.getSource() == itemSIOX) {
            IJ.run("SIOX Segmentation");
        } else if (e.getSource() == itemWatershed) {
            IJ.run("Watershed");
        } else if (e.getSource() == itemContourPlotter) {
            IJ.run("ContourPlotter ");
        } else if (e.getSource() == itemDottedandDashedLines) {
            IJ.run("Dotted Line");
        } else if (e.getSource() == itemFeatureJ) {
            IJ.run("FeatureJ...");
        } else if (e.getSource() == itemFlowJ) {
            IJ.run("FlowJ");
        } else if (e.getSource() == itemFlow3J) {
            IJ.run("Flow3J");
        } else if (e.getSource() == itemObjectJ) {
            IJ.run("ObjectJ");
        } else if (e.getSource() == itemPCA) {
            IJ.run("PCA ");
        } else if (e.getSource() == itemPolarTransformer) {
            IJ.run("Polar Transformer");
        } else if (e.getSource() == itemRadialGrid) {
            IJ.run("Radial Grid");
        } else if (e.getSource() == itemRadialReslice) {
            IJ.run("Radial Reslice");
        } else if (e.getSource() == itemStackSlicer) {
            IJ.run("StackSlicer ");
        } else if (e.getSource() == itemStraightenCurvedObjects) {
            IJ.run("Straighten...");
        } else if (e.getSource() == itemSubstackMaker) {
            IJ.run("Substack Maker");
        } else if (e.getSource() == itemSurfaceJ) {
            IJ.run("SurfaceJ ");
        } else if (e.getSource() == itemSyncWindows) {
            IJ.run("Sync Windows");
        } else if (e.getSource() == itemTransformJ) {
            IJ.run("TransformJ...");
        } else if (e.getSource() == itemUntiltStack) {
            IJ.run("Untilt Stack");
        } else if (e.getSource() == itemVolumeJ) {
            IJ.run("VolumeJ ");
        } else if (e.getSource() == itemVolumeViewer3DSlicer) {
            IJ.run("Volume Viewer");
        } else if (e.getSource() == itemVoxelCounter) {
            IJ.run("Voxel Counter");
        } else if (e.getSource() == item3DViewer) {
            IJ.run("3D Viewer");
        } else if (e.getSource() == itemErode) {
            IJ.run("Make Binary");
            IJ.run("Erode");
        } else if (e.getSource() == itemDilate) {
            IJ.run("Make Binary");
            IJ.run("Dilate");
        } else if (e.getSource() == itemOpen) {
            IJ.run("Make Binary");
            IJ.run("Open");
        } else if (e.getSource() == itemClose) {
            IJ.run("Make Binary");
            IJ.run("Close-");
        } else if (e.getSource() == itemOutline) {
            IJ.run("Make Binary");
            IJ.run("Outline");
        } else if (e.getSource() == itemFillHoles) {
            IJ.run("Make Binary");
            IJ.run("Fill Holes");
        } else if (e.getSource() == itemSkeletonize) {
            IJ.run("Make Binary");
            IJ.run("Skeletonize");
        } else if (e.getSource() == itemDistanceMap) {
            IJ.run("Make Binary");
            IJ.run("Distance Map");
        } else if (e.getSource() == itemUltimatePoints) {
            IJ.run("Make Binary");
            IJ.run("Ultimate Points");
        } else if (e.getSource() == itemWatershed) {
            IJ.run("Make Binary");
            IJ.run("Watershed");
        } else if (e.getSource() == itemVoronoi) {
            IJ.run("Make Binary");
            IJ.run("Voronoi");
        } else if (e.getSource() == itemOptions) {
            IJ.run("Options...");
        }

        imp.updateAndDraw();
    }

    private void run3DViewer(ImagePlus ip) {
        Image3DUniverse universe = new Image3DUniverse(UNIVERSE_W, UNIVERSE_H);

        // Adds the sphere image plus to universe.
        new StackConverter(ip).convertToRGB();
        Content c = universe.addVoltex(ip);
        c.displayAs(Content.VOLUME);

        universe.show();    // Shows...
    }

    public static void main(String args[]) {
        JFrame frame = new JFrame("-- TEST --");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        ImagePlus ip = IJ.openImage("/home/juanjo/.gnome2/gnome-art/download/backgrounds/GNOME-Beach_1280x1024.jpg");
        XmippMenuBar menuBar = new XmippMenuBar(ip);
        frame.add(new JLabel(new ImageIcon(ip.getImage())), BorderLayout.CENTER);

        frame.setMenuBar(menuBar);
        frame.setSize(800, 600);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
