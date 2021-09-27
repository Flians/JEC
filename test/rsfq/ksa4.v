/*

ksa4:
	jxor: 8
	jspl: 16
	jcb: 4
	jdff: 17
	jand: 8

Summary:
	jxor: 8
	jspl: 16
	jcb: 4
	jdff: 17
	jand: 8
*/

module ksa4(a0, a1, a2, a3, cin, b0, b1, b2, b3, s0, s1, s2, s3, s4);
	input a0;
	input a1;
	input a2;
	input a3;
	input cin;
	input b0;
	input b1;
	input b2;
	input b3;
	output s0;
	output s1;
	output s2;
	output s3;
	output s4;
	wire n15;
	wire n17;
	wire n18;
	wire n19;
	wire n20;
	wire n22;
	wire n23;
	wire n24;
	wire n25;
	wire n27;
	wire n28;
	wire n29;
	wire n30;
	wire n32;
	wire n33;
	wire [1:0] w_a0_0;
	wire [1:0] w_a1_0;
	wire [1:0] w_a2_0;
	wire [1:0] w_a3_0;
	wire [1:0] w_cin_0;
	wire [1:0] w_b0_0;
	wire [1:0] w_b1_0;
	wire [1:0] w_b2_0;
	wire [1:0] w_b3_0;
	wire [1:0] w_n15_0;
	wire [1:0] w_n19_0;
	wire [1:0] w_n20_0;
	wire [1:0] w_n24_0;
	wire [1:0] w_n25_0;
	wire [1:0] w_n29_0;
	wire [1:0] w_n30_0;
	wire w_dff_B_7Vh1wBZ73_1;
	wire w_dff_B_z6YKB8Vn4_1;
	wire w_dff_B_PpAzvUpb5_1;
	wire w_dff_B_pcACyzf37_1;
	wire w_dff_B_fijP6Sut6_2;
	wire w_dff_B_V1B0kMTm9_2;
	wire w_dff_B_asnGRsG02_2;
	wire w_dff_B_aK5oAW9T3_1;
	wire w_dff_B_JIXgi1541_1;
	wire w_dff_B_udoI0CJS1_1;
	wire w_dff_B_AXUO6bKj4_2;
	wire w_dff_B_r63XUzAW2_2;
	wire w_dff_B_5ml5tt5G8_1;
	wire w_dff_B_bvSvS31r0_1;
	wire w_dff_B_sJiZGCkO0_2;
	wire w_dff_B_StFyEiId0_1;
	wire w_dff_B_miRqwzaG6_2;
	jxor g00(.dina(w_b0_0[1]),.dinb(w_a0_0[1]),.dout(n15));
	jxor g01(.dina(w_n15_0[1]),.dinb(w_cin_0[1]),.dout(s0));
	jand g02(.dina(w_b0_0[0]),.dinb(w_a0_0[0]),.dout(n17));
	jand g03(.dina(w_n15_0[0]),.dinb(w_cin_0[0]),.dout(n18));
	jcb g04(.dina(n18),.dinb(w_dff_B_StFyEiId0_1),.dout(n19));
	jxor g05(.dina(w_b1_0[1]),.dinb(w_a1_0[1]),.dout(n20));
	jxor g06(.dina(w_n20_0[1]),.dinb(w_n19_0[1]),.dout(s1));
	jand g07(.dina(w_b1_0[0]),.dinb(w_a1_0[0]),.dout(n22));
	jand g08(.dina(w_n20_0[0]),.dinb(w_n19_0[0]),.dout(n23));
	jcb g09(.dina(n23),.dinb(w_dff_B_bvSvS31r0_1),.dout(n24));
	jxor g10(.dina(w_b2_0[1]),.dinb(w_a2_0[1]),.dout(n25));
	jxor g11(.dina(w_n25_0[1]),.dinb(w_n24_0[1]),.dout(s2));
	jand g12(.dina(w_b2_0[0]),.dinb(w_a2_0[0]),.dout(n27));
	jand g13(.dina(w_n25_0[0]),.dinb(w_n24_0[0]),.dout(n28));
	jcb g14(.dina(n28),.dinb(w_dff_B_udoI0CJS1_1),.dout(n29));
	jxor g15(.dina(w_b3_0[1]),.dinb(w_a3_0[1]),.dout(n30));
	jxor g16(.dina(w_n30_0[1]),.dinb(w_n29_0[1]),.dout(s3));
	jand g17(.dina(w_b3_0[0]),.dinb(w_a3_0[0]),.dout(n32));
	jand g18(.dina(w_n30_0[0]),.dinb(w_n29_0[0]),.dout(n33));
	jcb g19(.dina(n33),.dinb(w_dff_B_pcACyzf37_1),.dout(s4));
	jspl jspl_w_a0_0(.douta(w_a0_0[0]),.doutb(w_a0_0[1]),.din(a0));
	jspl jspl_w_a1_0(.douta(w_a1_0[0]),.doutb(w_a1_0[1]),.din(a1));
	jspl jspl_w_a2_0(.douta(w_a2_0[0]),.doutb(w_a2_0[1]),.din(a2));
	jspl jspl_w_a3_0(.douta(w_a3_0[0]),.doutb(w_a3_0[1]),.din(a3));
	jspl jspl_w_cin_0(.douta(w_cin_0[0]),.doutb(w_cin_0[1]),.din(w_dff_B_miRqwzaG6_2));
	jspl jspl_w_b0_0(.douta(w_b0_0[0]),.doutb(w_b0_0[1]),.din(b0));
	jspl jspl_w_b1_0(.douta(w_b1_0[0]),.doutb(w_b1_0[1]),.din(b1));
	jspl jspl_w_b2_0(.douta(w_b2_0[0]),.doutb(w_b2_0[1]),.din(b2));
	jspl jspl_w_b3_0(.douta(w_b3_0[0]),.doutb(w_b3_0[1]),.din(b3));
	jspl jspl_w_n15_0(.douta(w_n15_0[0]),.doutb(w_n15_0[1]),.din(n15));
	jspl jspl_w_n19_0(.douta(w_n19_0[0]),.doutb(w_n19_0[1]),.din(n19));
	jspl jspl_w_n20_0(.douta(w_n20_0[0]),.doutb(w_n20_0[1]),.din(w_dff_B_sJiZGCkO0_2));
	jspl jspl_w_n24_0(.douta(w_n24_0[0]),.doutb(w_n24_0[1]),.din(n24));
	jspl jspl_w_n25_0(.douta(w_n25_0[0]),.doutb(w_n25_0[1]),.din(w_dff_B_r63XUzAW2_2));
	jspl jspl_w_n29_0(.douta(w_n29_0[0]),.doutb(w_n29_0[1]),.din(n29));
	jspl jspl_w_n30_0(.douta(w_n30_0[0]),.doutb(w_n30_0[1]),.din(w_dff_B_asnGRsG02_2));
	jdff dff_B_7Vh1wBZ73_1(.din(n32),.dout(w_dff_B_7Vh1wBZ73_1));
	jdff dff_B_z6YKB8Vn4_1(.din(w_dff_B_7Vh1wBZ73_1),.dout(w_dff_B_z6YKB8Vn4_1));
	jdff dff_B_PpAzvUpb5_1(.din(w_dff_B_z6YKB8Vn4_1),.dout(w_dff_B_PpAzvUpb5_1));
	jdff dff_B_pcACyzf37_1(.din(w_dff_B_PpAzvUpb5_1),.dout(w_dff_B_pcACyzf37_1));
	jdff dff_B_fijP6Sut6_2(.din(n30),.dout(w_dff_B_fijP6Sut6_2));
	jdff dff_B_V1B0kMTm9_2(.din(w_dff_B_fijP6Sut6_2),.dout(w_dff_B_V1B0kMTm9_2));
	jdff dff_B_asnGRsG02_2(.din(w_dff_B_V1B0kMTm9_2),.dout(w_dff_B_asnGRsG02_2));
	jdff dff_B_aK5oAW9T3_1(.din(n27),.dout(w_dff_B_aK5oAW9T3_1));
	jdff dff_B_JIXgi1541_1(.din(w_dff_B_aK5oAW9T3_1),.dout(w_dff_B_JIXgi1541_1));
	jdff dff_B_udoI0CJS1_1(.din(w_dff_B_JIXgi1541_1),.dout(w_dff_B_udoI0CJS1_1));
	jdff dff_B_AXUO6bKj4_2(.din(n25),.dout(w_dff_B_AXUO6bKj4_2));
	jdff dff_B_r63XUzAW2_2(.din(w_dff_B_AXUO6bKj4_2),.dout(w_dff_B_r63XUzAW2_2));
	jdff dff_B_5ml5tt5G8_1(.din(n22),.dout(w_dff_B_5ml5tt5G8_1));
	jdff dff_B_bvSvS31r0_1(.din(w_dff_B_5ml5tt5G8_1),.dout(w_dff_B_bvSvS31r0_1));
	jdff dff_B_sJiZGCkO0_2(.din(n20),.dout(w_dff_B_sJiZGCkO0_2));
	jdff dff_B_StFyEiId0_1(.din(n17),.dout(w_dff_B_StFyEiId0_1));
	jdff dff_B_miRqwzaG6_2(.din(cin),.dout(w_dff_B_miRqwzaG6_2));
endmodule