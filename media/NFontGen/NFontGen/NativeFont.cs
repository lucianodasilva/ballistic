
using System;
using System.Runtime.InteropServices;
using System.Text;
namespace NFontGen
{

#region Win32 API Declarations
 /// <summary>
 /// API declares
 /// </summary>

 const int DEFAULT_CHARSET = 1;
 const int FIXED_PITCH = 1;
 const int FF_DONTCARE = 0;

 [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Auto)]
       public struct LOGFONT
 { 
       public int lfHeight; 
       public int lfWidth; 
       public int lfEscapement; 
       public int lfOrientation; 
       public int lfWeight; 
       public byte lfItalic; 
       public byte lfUnderline; 
       public byte lfStrikeOut; 
       public byte lfCharSet; 
       public byte lfOutPrecision; 
       public byte lfClipPrecision; 
       public byte lfQuality; 
       public byte lfPitchAndFamily; 
       [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
       public string lfFaceName;
 }

 [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Auto)]
       public struct ENUMLOGFONTEX
 {
       public LOGFONT elfLogFont;
       [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
       public string elfFullName; 
       [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
       public string elfStyle;
       [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
       public string elfScript;
 }

 [StructLayout(LayoutKind.Sequential)]
       public struct NEWTEXTMETRIC
 {
       public int tmHeight;
       public int tmAscent;
       public int tmDescent;
       public int tmInternalLeading;
       public int tmExternalLeading;
       public int tmAveCharWidth;
       public int tmMaxCharWidth;
       public int tmWeight;
       public int tmOverhang;
       public int tmDigitizedAspectX;
       public int tmDigitizedAspectY;
       public byte tmFirstChar;
       public byte tmLastChar;
       public byte tmDefaultChar;
       public byte tmBreakChar;
       public byte tmItalic;
       public byte tmUnderlined;
       public byte tmStruckOut;
       public byte tmPitchAndFamily;
       public byte tmCharSet;
       public int ntmFlags;
       public int ntmSizeEM;
       public int ntmCellHeight;
       public int ntmAveWidth;
 }

 [StructLayout(LayoutKind.Sequential)]
       public struct FONTSIGNATURE
 {
       [MarshalAs(UnmanagedType.LPArray, SizeConst=4)] int[] fsUsb;
       [MarshalAs(UnmanagedType.LPArray, SizeConst=2)] int[] fsCsb;
 }

 [StructLayout(LayoutKind.Sequential)]
       public struct NEWTEXTMETRICEX
 {
       public NEWTEXTMETRIC ntmTm;
       public      FONTSIGNATURE ntmFontSig;
 }

 // see:
 // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/fontext_4mk8.asp
 [DllImport("gdi32.dll", CharSet=CharSet.Auto)] 
 internal static extern int EnumFontFamiliesEx( 
       System.IntPtr hdc, 
       ref LOGFONT lpLogfont, 
       EnumFontFamExProcDelegate lpEnumFontFamExProc, // callback function 
       int lParam, 
       uint dwFlags
 ); 

 #endregion


 // Delegate function
 // See:
 // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/cpguide/html/cpconUsingCallbackFunctions.asp
 public delegate int EnumFontFamExProcDelegate
 (
       IntPtr lpelfe, /* pointer to logical-font data */
       IntPtr lpntme, /* pointer to physical-font data */
       int FontType, /* type of font */
       int lParam /* a combo box HWND */
 );


 // Test the callback from a button click event
 private void button1_Click(object sender, System.EventArgs e)
 {
       LOGFONT logfont = new LOGFONT();
       Graphics g = this.CreateGraphics();
       IntPtr hdc = g.GetHdc();
       
       logfont.lfCharSet = DEFAULT_CHARSET;
       logfont.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
       logfont.lfFaceName = string.Empty;

       EnumFontFamExProcDelegate CallBackProc = new EnumFontFamExProcDelegate(TestClass.EnumFontFamExProc);
       EnumFontFamiliesEx(hdc, ref logfont, CallBackProc, 1, 0);

       g.ReleaseHdc(hdc);
 }

 // Callback function is called by Windows for each matching font
 // See:
 // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/fontext_9rmr.asp
 public static int EnumFontFamExProc(IntPtr lpelfe, IntPtr lpntme, int FontType, int lParam)
 {
       // Get the structure from the pointer
       ENUMLOGFONTEX elf = (ENUMLOGFONTEX)Marshal.PtrToStructure(lpelfe, typeof(ENUMLOGFONTEX));
       // The two low-order bits specify the pitch of the font.
       int paf = elf.elfLogFont.lfPitchAndFamily & 0x03;
       if (paf == FIXED_PITCH)
       {
             Console.WriteLine(elf.elfFullName + " - " + elf.elfScript);
       }
       return 1;
 }


}