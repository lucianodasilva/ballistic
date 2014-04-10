import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.*;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.text.Font;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.FileWriter;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

public class Controller implements Initializable {

    public static BufferedImage LastGenImage;

    @FXML
    public Button cmdGenerate;

    @FXML
    public Button cmdGenFile;

    @FXML
    public TextField txtSize;

    @FXML
    public ComboBox cmbFontName;

    @FXML
    public ComboBox cmbTextureSize;

    private ObservableList <String> AvailableFonts;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        List < String > fonts = Font.getFontNames();

        AvailableFonts = FXCollections.observableArrayList(fonts);

        cmbFontName.setCellFactory(new ComboCellFactory());
        cmbFontName.setItems(AvailableFonts);
    }

    public BufferedImage GenImage (String font_name, int font_size, int image_size, Color back, Color fore) {
        BufferedImage image = new BufferedImage(image_size, image_size, BufferedImage.TYPE_INT_ARGB);

        java.awt.Font font = new java.awt.Font (font_name, java.awt.Font.PLAIN, font_size);

        Graphics2D g2 = image.createGraphics();

        g2.setFont(font);
        g2.setBackground(back);
        g2.clearRect(0, 0, image_size, image_size);

        FontMetrics metrics = g2.getFontMetrics();

        int
                char_height = metrics.getAscent() + metrics.getDescent(),
                char_width = metrics.getMaxAdvance();

        int [] widths = metrics.getWidths();

        for ( char i = 0; i < 256; ++i){
            int cwidth = (int)metrics.getStringBounds(new char [] {i}, 0, 1, g2).getWidth();
            if (char_width < cwidth)
                char_width = cwidth;
        }

        int ascii = 0;

        for (int y = 0; y < image_size; y += char_height) {
            for (int x = 0; x < image_size; x+= char_width) {
                if (ascii < 256) {
                    String s = "" + (char) ascii;
                    g2.setColor(fore);
                    g2.drawString(s, x, y);
                }
                ++ascii;
            }
        }


        return image;
    }

    @FXML
    public void onGenerate () {

        int texture_width = Integer.parseInt((String)cmbTextureSize.getValue());

        LastGenImage = GenImage(
                (String)cmbFontName.getValue(),
                Integer.parseInt(txtSize.getText()),
                texture_width,
                Color.BLACK,
                Color.WHITE
        );

        try {
            // show image
            Parent root;

            root = FXMLLoader.load(getClass().getResource("image_view.fxml"));
            Stage stage = new Stage();
            stage.setTitle("Generated Font Resource");
            stage.setScene(new Scene(root, texture_width, texture_width));
            stage.show();

        } catch (java.io.IOException e) {
            e.printStackTrace();
        }

    }

    @FXML
    public void onGenerateFile () {

        int texture_width = Integer.parseInt((String)cmbTextureSize.getValue());

        BufferedImage image = GenImage(
                (String)cmbFontName.getValue(),
                Integer.parseInt(txtSize.getText()),
                texture_width,
                new Color (0,0,0,0),
                Color.WHITE
        );

        FileChooser fileChooser = new FileChooser();

        //Set extension filter
        FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("PNG files (*.png)", "*.png");
        fileChooser.getExtensionFilters().add(extFilter);

        //Show save file dialog
        File file = fileChooser.showSaveDialog(cmdGenerate.getScene().getWindow());

        if(file != null){

            try {
                ImageIO.write(image, "png", file);
            } catch (java.io.IOException e) {
                e.printStackTrace();
            }

        }


    }

}