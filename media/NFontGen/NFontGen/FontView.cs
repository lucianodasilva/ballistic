using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NFontGen
{
    public partial class FontView : Form
    {
        public FontView(string package_text)
        {
            InitializeComponent();

            txtMetrics.Text = package_text;
        }

        private void FontView_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            var saveDialog = new SaveFileDialog();
            saveDialog.CheckPathExists = true;
            saveDialog.Filter = "*.*|(*.*)";

            if (saveDialog.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return;

            System.IO.File.WriteAllText(saveDialog.FileName, txtMetrics.Text);
        }
    }
}
