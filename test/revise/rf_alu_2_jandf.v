`timescale 1ps/100fs

module rf_alu_2_jandf(xin, yin, carry_in, end_bar, cmpl_x, cmpl_y, op_and, op_xor, op_arith, zout, overflow, carry_out, clk);

input	[1:0] xin;
input  	[1:0] yin;
input	carry_in, end_bar, cmpl_x,
	cmpl_y,
	op_and,
	op_xor,
	op_arith,
	clk;

output  [1:0] zout;
output	carry_out, overflow;
wire	[8:0] w1;
wire	[8:0] w2;
wire	[7:0] w3;
wire	[8:0] w4;
wire	[7:0] w5;
wire	[8:0] w6;
wire    [5:0] wcb;
wire	[3:0] ws0;
wire	[7:0] ws1;
wire	[9:0] ws2;
wire	[9:0] ws3;
wire	[5:0] ws4;
wire	[2:0] ws5;
wire	[3:0] ws6;
wire	[3:0] wj3;
wire	[6:0] wj4;
wire	[6:0] wj5;
wire	[2:0] wj6;
wire     fb;

//----- line input ------

	jspl s01(.din(cmpl_x), .douta(ws0[0]), .doutb(ws0[1]));
	jspl s02(.din(cmpl_y), .douta(ws0[2]), .doutb(ws0[3]));

	//----- line 1 ------
	jdff d11(.din(op_arith), .dout(w1[0]), .clk(clk));
	jdff d12(.din(op_and  ), .dout(w1[1]), .clk(clk));
	jdff d13(.din(op_xor  ), .dout(w1[2]), .clk(clk));
	jxor x11(.dina(xin[0]), .dinb(ws0[1]), .dout(w1[3]), .clk(clk));
	jxor x12(.dina(yin[0]), .dinb(ws0[3]), .dout(w1[4]), .clk(clk));
	jxor x13(.dina(xin[1]), .dinb(ws0[0]), .dout(w1[5]), .clk(clk));
	jxor x14(.dina(yin[1]), .dinb(ws0[2]), .dout(w1[6]), .clk(clk));
	jdff d14(.din(end_bar ), .dout(w1[7]), .clk(clk));
	jdff d15(.din(carry_in), .dout(w1[8]), .clk(clk));


//------ line 2 -----
	jspl s11(.din(w1[3]), .douta(ws1[0]), .doutb(ws1[1]));
	jspl s12(.din(w1[4]), .douta(ws1[2]), .doutb(ws1[3]));
	jspl s13(.din(w1[5]), .douta(ws1[4]), .doutb(ws1[5]));
	jspl s14(.din(w1[6]), .douta(ws1[6]), .doutb(ws1[7]));

	jdff d21(.din(w1[0]), .dout(w2[0]), .clk(clk));
	jdff d22(.din(w1[1]), .dout(w2[1]), .clk(clk));
	jdff d23(.din(w1[2]), .dout(w2[2]), .clk(clk));

	jxor x21(.dina(ws1[0]), .dinb(ws1[3]), .dout(w2[3]), .clk(clk));
	jxor a21(.dina(ws1[1]), .dinb(ws1[2]), .dout(w2[4]), .clk(clk));
	jxor x22(.dina(ws1[4]), .dinb(ws1[7]), .dout(w2[5]), .clk(clk));
	jand a22(.dina(ws1[5]), .dinb(ws1[6]), .dout(w2[6]), .clk(clk));

	jdff d24(.din(w1[7] ), .dout(w2[7]), .clk(clk));
	jdff d25(.din(w1[8] ), .dout(w2[8]), .clk(clk));


//------ line 3 -----------
	jspl s21(.din(w2[4]), .douta(ws2[0]), .doutb(ws2[1]));
	jspl s22(.din(w2[6]), .douta(ws2[2]), .doutb(ws2[3]));
	jspl s23(.din(w2[2]), .douta(ws2[4]), .doutb(ws2[5]));
	jspl s24(.din(w2[1]), .douta(ws2[6]), .doutb(ws2[7]));
	jspl s25(.din(w2[0]), .douta(ws2[8]), .doutb(ws2[9]));


	jand a31(.dina(w2[3]), .dinb(ws2[4]), .dout(w3[0]), .clk(clk));
	jand a32(.dina(ws2[1]), .dinb(ws2[6]), .dout(w3[1]), .clk(clk));
	jand a33(.dina(ws2[0]), .dinb(ws2[8]), .dout(w3[2]), .clk(clk));
	jand a34(.dina(w2[5]), .dinb(ws2[5]), .dout(w3[3]), .clk(clk));
	jand a35(.dina(ws2[3]), .dinb(ws2[7]), .dout(w3[4]), .clk(clk));
	jand a36(.dina(ws2[2]), .dinb(ws2[9]), .dout(w3[5]), .clk(clk));

	jdff d31(.din(w2[7] ), .dout(w3[6]), .clk(clk));
	jdff d32(.din(w2[8] ), .dout(w3[7]), .clk(clk));

//------ line 4 ------

	jcb  cb1(.dina(w3[0]), .dinb(w3[1]), .dout(wcb[0]));
	jcb  cb2(.dina(w3[3]), .dinb(w3[4]), .dout(wcb[1]));

	jspl s31(.din(wcb[0]), .douta(ws3[0]), .doutb(ws3[1]));
	jspl s32(.din(ws3[1]), .douta(ws3[2]), .doutb(ws3[3]));
	jspl s33(.din(w3[2]), .douta(ws3[4]), .doutb(ws3[5]));
	jspl s34(.din(wcb[1]), .douta(ws3[6]), .doutb(ws3[7]));
	jspl s35(.din(ws3[7]), .douta(ws3[8]), .doutb(ws3[9]));

	jdff d41(.din(ws3[0]), .dout(w4[0]), .clk(clk));
	jdff d42(.din(ws3[2]), .dout(w4[1]), .clk(clk));
	jdff d43(.din(ws3[4]), .dout(w4[2]), .clk(clk));
	jdff d44(.din(ws3[6]), .dout(w4[3]), .clk(clk));

	jand a41(.dina(ws3[3]), .dinb((ws3[8])), .dout(w4[4]), .clk(clk));
	jand a42(.dina(ws3[5]), .dinb((ws3[9])), .dout(w4[5]), .clk(clk));

	jdff d45(.din(w3[5] ), .dout(w4[6]), .clk(clk));
	jdff d46(.din(w3[6] ), .dout(w4[7]), .clk(clk));
	jdff d47(.din(w3[7] ), .dout(w4[8]), .clk(clk));

//------ line 5 ------

	jcb  cb3(.dina(w4[5]), .dinb(w4[6]), .dout(wcb[2]));

	jspl s41(.din(w4[4]), .douta(ws4[0]), .doutb(ws4[1]));
	jspl s42(.din(wcb[2]), .douta(ws4[2]), .doutb(ws4[3]));
	jspl s43(.din(w4[7]), .douta(ws4[4]), .doutb(ws4[5]));

	jdff d51(.din(w4[0] ), .dout(w5[0]), .clk(clk));
	jdff d52(.din(w4[1] ), .dout(w5[1]), .clk(clk));
	jdff d53(.din(w4[2] ), .dout(w5[2]), .clk(clk));
	jdff d54(.din(w4[3] ), .dout(w5[3]), .clk(clk));
	jdff d55(.din(ws4[0] ), .dout(w5[4]), .clk(clk));
	jdff d56(.din(ws4[2] ), .dout(w5[5]), .clk(clk));

	jand a51(.dina(ws4[1]), .dinb(ws4[5]), .dout(w5[6]), .clk(clk));
	jand a52(.dina(ws4[3]), .dinb(ws4[4]), .dout(w5[7]), .clk(clk));


//------ line 6 ------

	jcb  cb4(.dina(w5[7]), .dinb(w4[8]), .dout(wcb[3]));

	jandf af1(.dina(wcb[3]), .dinb(w5[6]), .dout(fb), .clk(clk));

	jspl3 s3p51(.din(fb), .douta(ws5[2]), .doutb(ws5[1]), .doutc(ws5[0]));

	jdff d61(.din(ws5[0]), .dout(w6[0]), .clk(clk));
	jdff d62(.din(w5[0]), .dout(w6[1]), .clk(clk));

	jand a61(.dina(ws5[1]), .dinb(w5[1]), .dout(w6[2]), .clk(clk));

	jdff d63(.din(w5[2]), .dout(w6[3]), .clk(clk));
	jdff d64(.din(w5[3]), .dout(w6[4]), .clk(clk));

	jand a62(.dina(ws5[2]), .dinb(w5[4]), .dout(w6[5]), .clk(clk));

	jdff d65(.din(w5[5]), .dout(w6[6]), .clk(clk));


//------ line 7 ------

	jcb  cb5(.dina(w6[2]), .dinb(w6[3]), .dout(wcb[4]));
	jcb  cb6(.dina(w6[5]), .dinb(w6[6]), .dout(wcb[5]));

	jspl s61(.din(wcb[4]), .douta(ws6[0]), .doutb(ws6[1]));
	jspl s62(.din(wcb[5]), .douta(ws6[2]), .doutb(ws6[3]));

	jxor x71(.dina(w6[0]), .dinb(w6[1]), .dout(zout[0]), .clk(clk));
	jxor x72(.dina(ws6[0]), .dinb(w6[4]), .dout(zout[1]), .clk(clk));
	jxor x73(.dina(ws6[1]), .dinb(ws6[3]), .dout(overflow), .clk(clk));

	jdff d71(.din(ws6[2]), .dout(carry_out), .clk(clk));

endmodule