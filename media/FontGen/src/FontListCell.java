import javafx.scene.control.ListCell;
import javafx.scene.text.Font;

/**
 * Created by Luciano on 09-Apr-14.
 */
public class FontListCell extends ListCell < String > {

    private final double defaultFontSize;

    public FontListCell() {
        // The default font size is cached here
        defaultFontSize = Font.getDefault().getSize();
    }

    protected void updateItem(String value, boolean empty) {
        super.updateItem(value, empty);
        if(!empty) {
            setText(value);

            Font font = new Font(value, defaultFontSize);
            setFont(font);
        }
    }

}
