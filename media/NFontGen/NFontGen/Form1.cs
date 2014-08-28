using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NFontGen
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // load installed fonts
            var font_collection = new InstalledFontCollection();

            foreach (var font_family in font_collection.Families)
            {
                cmbFonts.Items.Add(font_family.Name);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            int texture_res = int.Parse (cmbTextureSize.Text);
            var buffer = new Bitmap(texture_res, texture_res);
            var g = Graphics.FromImage((Image)buffer);

            FontStyle font_style = FontStyle.Regular;

            if (chkBold.Checked)
                font_style |= FontStyle.Bold;

            if (chkItalic.Checked)
                font_style |= FontStyle.Italic;

            var font = new Font (cmbFonts.Text, float.Parse (cmbFontSize.Text), font_style, GraphicsUnit.Point);

            int stride = texture_res / 16;

            g.Clear (Color.Transparent);

            string metrics = "";

            for (int y = 0; y < 16; ++y) {
                for (int x = 0; x < 16; ++x)
                {
                    char v = (char)(y * 16 + x);
                    string vs = v.ToString();

                    g.DrawString(vs, font, Brushes.White, x * stride, y * stride);

                    var size = g.MeasureString(vs, font);

                    if (x != 0 && y != 0)
                        metrics += ",";

                    metrics += size.Width.ToString() + "," + size.Height.ToString();
                }
            }

            txtMetrics.Text = metrics;

            var new_texture_view = new TextureView(buffer);
            new_texture_view.Show();
            
        }

    }
}
