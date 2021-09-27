/*

one_full_adder:
	jxor: 2
	jspl: 4
	jcb: 1
	jdff: 2
	jand: 2

Summary:
	jxor: 2
	jspl: 4
	jcb: 1
	jdff: 2
	jand: 2

The maximum logic level gap of any gate:
	one_full_adder: 1
*/

`timescale  1ps  /  100fs
module adder_1(A, B, Carry_in, clk, Sum, Carry_out);
	input A;
	input B;
	input Carry_in;
	input clk;
	output Sum;
	output Carry_out;
	wire [8:0] ds;
	wire [1:0] w_A_0;
	wire [1:0] w_B_0;
	jdff dff_0_0(.din(Carry_in),.dout(ds[0]),.clk(clk));
	jxor xor_0_0(.dina(w_A_0[1]),.dinb(w_B_0[1]),.dout(ds[1]),.clk(clk));
	jand and_0_0(.dina(w_A_0[0]),.dinb(w_B_0[0]),.dout(ds[2]),.clk(clk));
	jspl spl_0_0(.din(ds[0]),.douta(ds[3]),.doutb(ds[4]));
	jspl spl_0_1(.din(ds[1]),.douta(ds[5]),.doutb(ds[6]));
	jxor xor_1_0(.dina(ds[3]),.dinb(ds[5]),.dout(Sum),.clk(clk));
	jand and_1_0(.dina(ds[4]),.dinb(ds[6]),.dout(ds[7]),.clk(clk));
	jdff dff_1_0(.din(ds[2]),.dout(ds[8]),.clk(clk));
	jcb cb_1_0(.dina(ds[7]),.dinb(ds[8]),.dout(Carry_out));
	jspl jspl_w_A_0(.douta(w_A_0[0]),.doutb(w_A_0[1]),.din(A));
	jspl jspl_w_B_0(.douta(w_B_0[0]),.doutb(w_B_0[1]),.din(B));
endmodule