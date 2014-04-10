import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.text.Font;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

public class ImageController implements Initializable {

    @FXML
    public ImageView imgView;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        Image image = javafx.embed.swing.SwingFXUtils.toFXImage(Controller.LastGenImage, null);
        imgView.setImage(image);
        imgView.setFitWidth(image.getWidth());
        imgView.setFitHeight(image.getHeight());
    }

}
