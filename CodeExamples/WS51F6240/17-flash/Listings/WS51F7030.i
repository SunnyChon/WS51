
#line 1 "WS51F7030.c" /0
 
 xdata unsigned char P00F	    _at_ 0x8000;	  
 xdata unsigned char P01F	    _at_ 0x8001;	  
 xdata unsigned char P02F	    _at_ 0x8002;	  
 xdata unsigned char P03F	    _at_ 0x8003;	  
 xdata unsigned char P04F	    _at_ 0x8004;	  
 xdata unsigned char P05F	    _at_ 0x8005;	  
 xdata unsigned char P06F	    _at_ 0x8006;	  
 xdata unsigned char P07F	    _at_ 0x8007;	  
 
 xdata unsigned char P10F	    _at_ 0x8008;
 xdata unsigned char P11F	    _at_ 0x8009;
 xdata unsigned char P12F	    _at_ 0x800a;
 xdata unsigned char P13F	    _at_ 0x800b;
 xdata unsigned char P14F	    _at_ 0x800c;
 xdata unsigned char P15F	    _at_ 0x800d;
 xdata unsigned char P16F	    _at_ 0x800e;
 xdata unsigned char P17F	    _at_ 0x800f;
 
 xdata unsigned char P20F	    _at_ 0x8010;	  
 xdata unsigned char P21F	    _at_ 0x8011;	  
 
 xdata unsigned char P30F	    _at_ 0x8018;
 xdata unsigned char P31F	    _at_ 0x8019;
 xdata unsigned char P32F	    _at_ 0x801a;
 xdata unsigned char P33F	    _at_ 0x801b;
 xdata unsigned char P34F	    _at_ 0x801c;
 xdata unsigned char P35F	    _at_ 0x801d;
 xdata unsigned char P36F	    _at_ 0x801e;	 
 xdata unsigned char P37F	    _at_ 0x801f;	 
 
 
 xdata unsigned char PWMEN     _at_ 0x8040;
 xdata unsigned char PWMIE 	  _at_ 0x8042;
 xdata unsigned char PWMFLG	  _at_ 0x8044;
 
 xdata unsigned char PWM0CFG 	_at_ 0x8050;
 xdata unsigned char PWM0PS	 	_at_ 0x8051;	 
 xdata unsigned char PWM0DUTL	_at_ 0x8054;
 xdata unsigned char PWM0DUTH	_at_ 0x8055;
 xdata unsigned char PWM0DIVL	_at_ 0x8056;
 xdata unsigned char PWM0DIVH	_at_ 0x8057;
 xdata unsigned char PWM1PS	 	_at_ 0x8059;	 
 xdata unsigned char PWM1DUTL	_at_ 0x805c;
 xdata unsigned char PWM1DUTH	_at_ 0x805d;
 xdata unsigned char PWM1DIVL	_at_ 0x805e;
 xdata unsigned char PWM1DIVH	_at_ 0x805f;
 
 xdata unsigned char PWM2CFG 	_at_ 0x8060;
 xdata unsigned char PWM2PS	 	_at_ 0x8061;	 
 xdata unsigned char PWM2DUTL	_at_ 0x8064;
 xdata unsigned char PWM2DUTH	_at_ 0x8065;
 xdata unsigned char PWM2DIVL	_at_ 0x8066;
 xdata unsigned char PWM2DIVH	_at_ 0x8067;
 xdata unsigned char PWM3PS	 	_at_ 0x8069;	 
 xdata unsigned char PWM3DUTL	_at_ 0x806c;
 xdata unsigned char PWM3DUTH	_at_ 0x806d;
 xdata unsigned char PWM3DIVL	_at_ 0x806e;
 xdata unsigned char PWM3DIVH	_at_ 0x806f;
 
 xdata unsigned char PWM4CFG 	_at_ 0x8070;
 xdata unsigned char PWM4PS	 	_at_ 0x8071;	 
 xdata unsigned char PWM4DUTL	_at_ 0x8074;
 xdata unsigned char PWM4DUTH	_at_ 0x8075;
 xdata unsigned char PWM4DIVL	_at_ 0x8076;
 xdata unsigned char PWM4DIVH	_at_ 0x8077;
 xdata unsigned char PWM5PS	 	_at_ 0x8079;	 
 xdata unsigned char PWM5DUTL	_at_ 0x807c;
 xdata unsigned char PWM5DUTH	_at_ 0x807d;
 xdata unsigned char PWM5DIVL	_at_ 0x807e;
 xdata unsigned char PWM5DIVH	_at_ 0x807f;
 
 xdata unsigned char PWM6CFG 	_at_ 0x8080;	 
 xdata unsigned char PWM6PS	 	_at_ 0x8081;	 
 xdata unsigned char PWM6DUTL	_at_ 0x8084;	 
 xdata unsigned char PWM6DUTH	_at_ 0x8085;	 
 xdata unsigned char PWM6DIVL	_at_ 0x8086;	 
 xdata unsigned char PWM6DIVH	_at_ 0x8087;	 
 xdata unsigned char PWM7PS	 	_at_ 0x8089;	 
 xdata unsigned char PWM7DUTL	_at_ 0x808c;	 
 xdata unsigned char PWM7DUTH	_at_ 0x808d;	 
 xdata unsigned char PWM7DIVL	_at_ 0x808e;	 
 xdata unsigned char PWM7DIVH	_at_ 0x808f;	 
 
 
 xdata unsigned char PIMOD	_at_ 0x80e8;	 
 xdata unsigned char P0IMSK	_at_ 0x80e9;	 
 xdata unsigned char P1IMSK	_at_ 0x80ea;	 
 xdata unsigned char P2IMSK	_at_ 0x80eb;	 
 xdata unsigned char P3IMSK	_at_ 0x80ec;	 
 
 xdata unsigned char BZ0CON	_at_ 0x80F0;	 
 xdata unsigned char BZ0PSC	_at_ 0x80F1;	 
 xdata unsigned char BZ0DUT	_at_ 0x80F2;	 
 xdata unsigned char BZ0DIV	_at_ 0x80F3;	 
 
 
 xdata unsigned char BZ1CON	_at_ 0x80F4;	 
 xdata unsigned char BZ1PSC	_at_ 0x80F5;	 
 xdata unsigned char BZ1DUT	_at_ 0x80F6;	 
 xdata unsigned char BZ1DIV	_at_ 0x80F7;	 
 
 
 
 xdata unsigned char TKPCS0	  _at_ 0x80f8;
 xdata unsigned char TKPCS1	  _at_ 0x80f9;
 xdata unsigned char TKPCS2	  _at_ 0x80fa;
 xdata unsigned char TKPCS3	  _at_ 0x80fB;	 
 xdata unsigned char TKPCS4	  _at_ 0x80fc;	 
 xdata unsigned char TKPCS5	  _at_ 0x80fd;	 
 
 xdata unsigned char TK0MXL    _at_ 0x8100;
 xdata unsigned char TK0MXH    _at_ 0x8101;
 xdata unsigned char TK1MXL    _at_ 0x8102;
 xdata unsigned char TK1MXH    _at_ 0x8103;
 xdata unsigned char TK2MXL    _at_ 0x8104;
 xdata unsigned char TK2MXH    _at_ 0x8105;
 xdata unsigned char TK3MXL    _at_ 0x8106;
 xdata unsigned char TK3MXH    _at_ 0x8107;
 xdata unsigned char TK4MXL    _at_ 0x8108;
 xdata unsigned char TK4MXH    _at_ 0x8109;
 xdata unsigned char TK5MXL    _at_ 0x810a;
 xdata unsigned char TK5MXH    _at_ 0x810b;
 xdata unsigned char TK6MXL    _at_ 0x810c;
 xdata unsigned char TK6MXH    _at_ 0x810d;
 xdata unsigned char TK7MXL    _at_ 0x810e;
 xdata unsigned char TK7MXH    _at_ 0x810f;
 xdata unsigned char TK8MXL    _at_ 0x8110;
 xdata unsigned char TK8MXH    _at_ 0x8111;
 xdata unsigned char TK9MXL    _at_ 0x8112;
 xdata unsigned char TK9MXH    _at_ 0x8113;
 xdata unsigned char TK10MXL   _at_ 0x8114;
 xdata unsigned char TK10MXH   _at_ 0x8115;
 xdata unsigned char TK11MXL   _at_ 0x8116;
 xdata unsigned char TK11MXH   _at_ 0x8117;
 
 xdata unsigned char TK0MNL    _at_ 0x8140;
 xdata unsigned char TK0MNH    _at_ 0x8141;
 xdata unsigned char TK1MNL    _at_ 0x8142;
 xdata unsigned char TK1MNH    _at_ 0x8143;
 xdata unsigned char TK2MNL    _at_ 0x8144;
 xdata unsigned char TK2MNH    _at_ 0x8145;
 xdata unsigned char TK3MNL    _at_ 0x8146;
 xdata unsigned char TK3MNH    _at_ 0x8147;
 xdata unsigned char TK4MNL    _at_ 0x8148;
 xdata unsigned char TK4MNH    _at_ 0x8149;
 xdata unsigned char TK5MNL    _at_ 0x814a;
 xdata unsigned char TK5MNH    _at_ 0x814b;
 xdata unsigned char TK6MNL    _at_ 0x814c;
 xdata unsigned char TK6MNH    _at_ 0x814d;
 xdata unsigned char TK7MNL    _at_ 0x814e;
 xdata unsigned char TK7MNH    _at_ 0x814f;
 xdata unsigned char TK8MNL    _at_ 0x8150;
 xdata unsigned char TK8MNH    _at_ 0x8151;
 xdata unsigned char TK9MNL    _at_ 0x8152;
 xdata unsigned char TK9MNH    _at_ 0x8153;
 xdata unsigned char TK10MNL   _at_ 0x8154;
 xdata unsigned char TK10MNH   _at_ 0x8155;
 xdata unsigned char TK11MNL   _at_ 0x8156;
 xdata unsigned char TK11MNH   _at_ 0x8157;
 
 xdata unsigned char TK0MSL    _at_ 0x8180;
 xdata unsigned char TK0MSH    _at_ 0x8181;
 xdata unsigned char TK1MSL    _at_ 0x8182;
 xdata unsigned char TK1MSH    _at_ 0x8183;
 xdata unsigned char TK2MSL    _at_ 0x8184;
 xdata unsigned char TK2MSH    _at_ 0x8185;
 xdata unsigned char TK3MSL    _at_ 0x8186;
 xdata unsigned char TK3MSH    _at_ 0x8187;
 xdata unsigned char TK4MSL    _at_ 0x8188;
 xdata unsigned char TK4MSH    _at_ 0x8189;
 xdata unsigned char TK5MSL    _at_ 0x818a;
 xdata unsigned char TK5MSH    _at_ 0x818b;
 xdata unsigned char TK6MSL    _at_ 0x818c;
 xdata unsigned char TK6MSH    _at_ 0x818d;
 xdata unsigned char TK7MSL    _at_ 0x818e;
 xdata unsigned char TK7MSH    _at_ 0x818f;
 xdata unsigned char TK8MSL    _at_ 0x8190;
 xdata unsigned char TK8MSH    _at_ 0x8191;
 xdata unsigned char TK9MSL    _at_ 0x8192;
 xdata unsigned char TK9MSH    _at_ 0x8193;
 xdata unsigned char TK10MSL   _at_ 0x8194;
 xdata unsigned char TK10MSH   _at_ 0x8195;
 xdata unsigned char TK11MSL   _at_ 0x8196;
 xdata unsigned char TK11MSH   _at_ 0x8197;
 
 
 xdata unsigned char TK0PS	_at_ 0x81C0;	 
 xdata unsigned char TK1PS	_at_ 0x81C1;	 
 xdata unsigned char TK2PS	_at_ 0x81C2;	 
 xdata unsigned char TK3PS	_at_ 0x81C3;	 
 xdata unsigned char TK4PS	_at_ 0x81C4;	 
 xdata unsigned char TK5PS	_at_ 0x81C5;	 
 xdata unsigned char TK6PS	_at_ 0x81C6;	 
 xdata unsigned char TK7PS	_at_ 0x81C7;	 
 xdata unsigned char TK8PS	_at_ 0x81C8;	 
 xdata unsigned char TK9PS	_at_ 0x81C9;	 
 xdata unsigned char TK10PS	_at_ 0x81Ca;	 
 xdata unsigned char TK11PS	_at_ 0x81Cb;	 
 
 
 
 xdata unsigned char LXDAT00	_at_ 0x8200;	 
 xdata unsigned char LXDAT01	_at_ 0x8201;	 
 xdata unsigned char LXDAT02	_at_ 0x8202;	 
 xdata unsigned char LXDAT03	_at_ 0x8203;	 
 xdata unsigned char LXDAT04	_at_ 0x8204;	 
 xdata unsigned char LXDAT05	_at_ 0x8205;	 
 xdata unsigned char LXDAT06	_at_ 0x8206;	 
 xdata unsigned char LXDAT07	_at_ 0x8207;	 
 xdata unsigned char LXDAT08	_at_ 0x8208;	 
 xdata unsigned char LXDAT09	_at_ 0x8209;	 
 xdata unsigned char LXDAT10	_at_ 0x820a;	 
 xdata unsigned char LXDAT11	_at_ 0x820b;	 
 xdata unsigned char LXDAT12	_at_ 0x820c;	 
 xdata unsigned char LXDAT13	_at_ 0x820d;	 
 xdata unsigned char LXDAT14	_at_ 0x820e;	 
 xdata unsigned char LXDAT15	_at_ 0x820f;	 
 xdata unsigned char LXDAT16	_at_ 0x8210;	 
 xdata unsigned char LXDAT17	_at_ 0x8211;	 
 xdata unsigned char LXDAT18	_at_ 0x8212;	 
 
 
 xdata unsigned char LSCON    	_at_ 0x8290;
 xdata unsigned char LSCFG    	_at_ 0x8291;
 xdata unsigned char LSDTM0   	_at_ 0x8293;
 xdata unsigned char LSDTM1   	_at_ 0x8294;
 xdata unsigned char LSPTM0   	_at_ 0x8295;
 xdata unsigned char LSPTM1   	_at_ 0x8296;
 xdata unsigned char LSCOM    	_at_ 0x8297;
 
 xdata unsigned char LSPE0     _at_ 0x8298;
 xdata unsigned char LSPE1     _at_ 0x8299;
 xdata unsigned char LSPE2	  _at_ 0x829a;	 
 
 
 xdata unsigned char LSDAT0    _at_ 0x82a0;
 xdata unsigned char LSDAT1    _at_ 0x82a1;
 xdata unsigned char LSDAT2    _at_ 0x82a2;	 
 
 xdata unsigned char MECON 	  _at_ 0x8300;
 xdata unsigned char FSCMD 	  _at_ 0x8301;
 xdata unsigned char BTMSK 	  _at_ 0x8302;
 xdata unsigned char FSDAT 	  _at_ 0x8303;
 xdata unsigned char FSFLG 	  _at_ 0x8304;
 xdata unsigned char PADR  	  _at_ 0x8305;
 xdata unsigned char FSADRL	  _at_ 0x8306;
 xdata unsigned char FSADRH	  _at_ 0x8307;
 
 xdata unsigned char CKSUML 	  _at_ 0x8308;
 xdata unsigned char CKSUMH 	  _at_ 0x8309;
 xdata unsigned char IDCODE0	  _at_ 0x830a;
 xdata unsigned char IDCODE1	  _at_ 0x830b;
 xdata unsigned char IDCODE2	  _at_ 0x830c;
 
 xdata unsigned char CHIPIDL	  _at_ 0x8400;
 xdata unsigned char CHIPIDH	  _at_ 0x8401;
 
 
 xdata unsigned char SPMAX	  _at_ 0x8407;	 
 
 
 
 
