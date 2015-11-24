
char buff[1024];
int r, w = 0;
char chars[256] = "--1234567890'^--qwertzuiopè¨:-asdfghjklea$-<yxcvbnm,.--";
char chars_maj[256] = "--+\"*ç%&/()=?`--QWERTZUIOPE!:-ASDFGHJKLoa£->YXCVBNM;:--";
// http://flint.cs.yale.edu/cs422/doc/art-of-asm/pdf/APNDXC.PDF
int k_shift_d = 0x2a;
int k_shift_u = 0xaa;
int k_backspace = 0x0e;
int k_ctrl = 0x1d;
int k_cmd = 91;
int k_alt = 0x38;
int k_enter = 0x1c;
int k_arrow_l = 0xe04b;
int k_arrow_r = 0xe04d;

int shift_pressed = 0;


void keyboard_init() {

}

void keyboard_handler() {
    int character = (int)(inb(0x60));
    if ((character >> 7) == 0)
    {
        // Le charactère est appuyé
        if(character == k_shift_d) shift_pressed = 1;
        if(character == k_shift_u) shift_pressed = 0;

        if(shift_pressed == 1) buff[w++] = chars_maj[character];
            else buff[w++] = chars[character];

    }
}

int getc() {
    int ret;
    while(r < w)
    {
        ret = buff[r++];
        printf("%c", ret);
    }
    return ret;
}
