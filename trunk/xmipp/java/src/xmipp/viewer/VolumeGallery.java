package xmipp.viewer;

import ij.ImagePlus;
import xmipp.ij.XmippImageConverter;
import xmipp.jni.ImageGeneric;

public class VolumeGallery extends ImageGallery {
	
	public VolumeGallery(GalleryData data) throws Exception {
		super(data);
		normalize = true; // volumes are displayed with global normalization by
							// default
		calculateMinAndMax();
	}

	private static final long serialVersionUID = 1L;

	// Load initial dimensions
	protected ImageDimension loadDimension() throws Exception {
		ImageGeneric image = new ImageGeneric(data.selectedVol); // read image header
		ImageDimension dim = new ImageDimension(image);
		image.destroy();
		return dim;
	}

	@Override
	protected double[] getMinAndMax() {
		try {
			ImageGeneric image = new ImageGeneric(data.selectedVol);
			image.read(ImageGeneric.FIRST_IMAGE);
			double[] stats = image.getStatistics();
			image.destroy();
			return stats;
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return null;
	}

	@Override
	protected String getItemKey(int index) throws Exception {
		return String.format("%d_(%d,%d)", index, thumb_width, thumb_height);
	}
	
	@Override
	public String getTitle() {
		return String.format("Volume: %s (%d x %d x %d)", data.selectedVol, image_width, image_height, n);
	}

	@Override
	protected ImageItem createItem(int index, String key) throws Exception {
		ImageGeneric image = new ImageGeneric(data.selectedVol);
		ImagePlus imp = XmippImageConverter.convertToImageJ(image, thumb_width,
				thumb_height, index + 1, ImageGeneric.FIRST_IMAGE);
		image.destroy();
		String label = String.format("%d", index + 1);
		return new ImageItem(key, label, imp);
	}

}
