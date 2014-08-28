using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NFontGen
{
    public partial class TextureView : Form
    {

        private Bitmap _bitmap;

        public TextureView(Bitmap bitmap)
        {
            _bitmap = bitmap;
            InitializeComponent();

            this.BackgroundImage = _bitmap;
            this.ClientSize = _bitmap.Size;
        }

        private void TextureView_Load(object sender, EventArgs e)
        {

        }
    }
}
