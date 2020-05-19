`timescale 1ps/100fs

module one_full_adder(A, B, Carry_in, clk, Sum, Carry_out);
	input A, B, Carry_in, clk;
	output Carry_out, Sum;
	wire[8:0] ds;
	//the first stage
	jdff dff_0_0(.din(Carry_in), .dout(ds[0]), .clk(clk));
	jxor xor_0_0(.dina(A), .dinb(B), .dout(ds[1]), .clk(clk));
	jand and_0_0(.dina(A), .dinb(B), .dout(ds[2]), .clk(clk));
	jspl spl_0_0(.din(ds[0]), .douta(ds[3]), .doutb(ds[4]));
	jspl spl_0_1(.din(ds[1]), .douta(ds[5]), .doutb(ds[6]));
	//the second stage
	jxor xor_1_0(.dina(ds[3]), .dinb(ds[5]), .dout(Sum), .clk(clk));
	jand and_1_0(.dina(ds[4]), .dinb(ds[6]), .dout(ds[7]), .clk(clk));
	jdff dff_1_0(.din(ds[2]), .dout(ds[8]), .clk(clk));
	jcb cb_1_0(.dina(ds[7]), .dinb(ds[8]), .dout(Carry_out));
endmodule