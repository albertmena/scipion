package xmipp.viewer.particlepicker.training.gui;

import ij.ImagePlus;
import ij.ImageStack;
import ij.gui.ImageCanvas;
import java.awt.Dimension;
import java.awt.Panel;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JDialog;

import xmipp.jni.ImageGeneric;
import xmipp.utils.XmippMessage;
import xmipp.utils.XmippWindowUtil;

public class TemplatesJDialog extends JDialog {

	protected SingleParticlePickerJFrame frame;
	protected Panel templatespn;
	protected int width, height;

	public TemplatesJDialog(SingleParticlePickerJFrame frame) {
		super(frame);
		this.frame = frame;

		if(!frame.getParticlePicker().hasManualParticles())
			throw new IllegalArgumentException(XmippMessage.getEmptyFieldMsg("Particles"));

		initComponents();

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent winEvt) {
				resetTemplatesJDialog();
			}

		});
	}

	protected void resetTemplatesJDialog() {
		frame.templatesdialog = null;

	}

	public void loadTemplates(boolean resize) {

		try {
			ImageGeneric templates = frame.getParticlePicker().getTemplates();
			
			int size = frame.getParticlePicker().getSize();

			if (!frame.getParticlePicker().hasManualParticles()) {

				templatespn.removeAll();
				templatespn.setPreferredSize(new Dimension(
						(int) (size * templates.getNDim()), size));
				pack();
				return;
			}
			ImageStack stack = new ImagePlus(frame.getParticlePicker().getTemplatesFile()).getImageStack();
			templatespn.removeAll();
			ImagePlus template;
			for (int i = 1; i <= frame.getParticlePicker().getTemplatesNumber(); i ++) {
				template = new ImagePlus("", stack.getProcessor(i));
				templatespn.add(new ImageCanvas(template));

			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		templatespn.repaint();
		pack();
	}


	private void initComponents() {
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setTitle("Templates");
		templatespn = new Panel();
		add(templatespn);
		loadTemplates(true);
		XmippWindowUtil.setLocation(0.6f, 0, this);
		setVisible(true);
		setAlwaysOnTop(true);
		// this.addComponentListener(new java.awt.event.ComponentAdapter() {
		// public void componentResized(ComponentEvent e) {
		// loadTemplates(false);
		// }
		// });
	}

	public void close() {
		setVisible(false);
		dispose();

	}

}
