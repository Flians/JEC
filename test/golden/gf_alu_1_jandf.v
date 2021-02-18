/*

alu_no_jp_clk:
	jxor: 5
	jspl: 7
	jspl3: 2
	jcb: 4
	jdff: 20
	jand: 8

Summary:
	jxor: 5
	jspl: 7
	jspl3: 2
	jcb: 4
	jdff: 20
	jand: 8

The maximum logic level gap of any gate:
	alu_no_jp_clk: 0
*/

module gf_alu_1_jandf(clk, X, Y, Carry_in, End, Cmpl_X, Cmpl_Y, Op_XOR, Op_AND, Op_ARITH, Carry_out, Overflow, Sum);
	input clk;
	input X;
	input Y;
	input Carry_in;
	input End;
	input Cmpl_X;
	input Cmpl_Y;
	input Op_XOR;
	input Op_AND;
	input Op_ARITH;
	output Carry_out;
	output Overflow;
	output Sum;
	wire [10:0] dj0;
	wire [8:0] dj1;
	wire [12:0] dj2;
	wire [5:0] dj3;
	wire [14:0] dj4;
	jdff dff_0_0(.din(Carry_in),.dout(dj0[0]), .clk(clk));
	jdff dff_0_1(.din(End),.dout(dj0[1]), .clk(clk));
	jxor xor_0_0(.dina(Y),.dinb(Cmpl_Y),.dout(dj0[2]));
	jxor xor_0_1(.dina(X),.dinb(Cmpl_X),.dout(dj0[3]));
	jdff dff_0_2(.din(Op_XOR),.dout(dj0[4]), .clk(clk));
	jdff dff_0_3(.din(Op_AND),.dout(dj0[5]), .clk(clk));
	jdff dff_0_4(.din(Op_ARITH),.dout(dj0[6]), .clk(clk));

	jdff dff_1_0(.din(dj0[0]),.dout(dj1[0]), .clk(clk));
	jdff dff_1_1(.din(dj0[1]),.dout(dj1[1]), .clk(clk));
	jand and_1_0(.dina(dj0[2]),.dinb(dj0[3]),.dout(dj1[2]));
	jxor xor_1_0(.dina(dj0[2]),.dinb(dj0[3]),.dout(dj1[3]));
	jdff dff_1_2(.din(dj0[4]),.dout(dj1[4]), .clk(clk));
	jdff dff_1_3(.din(dj0[5]),.dout(dj1[5]), .clk(clk));
	jdff dff_1_4(.din(dj0[6]),.dout(dj1[6]), .clk(clk));

	jdff dff_2_0(.din(dj1[0]),.dout(dj2[0]), .clk(clk));
	jdff dff_2_1(.din(dj1[1]),.dout(dj2[1]), .clk(clk));
	jand and_2_0(.dina(dj1[6]),.dinb(dj1[2]),.dout(dj2[2]));
	jand and_2_1(.dina(dj1[5]),.dinb(dj1[2]),.dout(dj2[3]));
	jand and_2_2(.dina(dj1[4]),.dinb(dj1[3]),.dout(dj2[4]));

	jcb cb_2_0(.dina(dj2[3]),.dinb(dj2[4]),.dout(dj2[9]));

	jxor and_3_0(.dina(dj2[2]),.dinb(dj2[1]),.dout(dj3[0]));
	jand and_3_1(.dina(dj2[9]),.dinb(dj2[1]),.dout(dj3[1]));
	jdff dff_3_0(.din(dj2[2]),.dout(dj3[2]), .clk(clk));
	jdff dff_3_1(.din(dj2[9]),.dout(dj3[3]), .clk(clk));
	jdff dff_3_2(.din(dj2[9]),.dout(dj3[4]), .clk(clk));
	jcb cb_3_0(.dina(dj3[0]),.dinb(dj2[0]),.dout(dj3[5]));
	jdff dff_4_0(.din(dj3[5]),.dout(dj4[0]), .clk(clk));
	jand and_4_0(.dina(dj3[1]),.dinb(dj4[2]),.dout(dj4[1]));
	jcb cb_4_0(.dina(dj4[0]),.dinb(dj4[1]),.dout(dj4[2]));

	jdff dff_4_1(.din(dj3[2]),.dout(dj4[6]), .clk(clk));
	jand and_4_1(.dina(dj3[3]),.dinb(dj4[2]),.dout(dj4[7]));
	jdff dff_4_2(.din(dj3[4]),.dout(dj4[8]), .clk(clk));
	jdff dff_4_3(.din(dj4[2]),.dout(dj4[9]), .clk(clk));
	jcb cb_4_1(.dina(dj4[6]),.dinb(dj4[7]),.dout(dj4[10]));

	jdff dff_5_0(.din(dj4[10]),.dout(Carry_out), .clk(clk));
	jxor xor_5_0(.dina(dj4[10]),.dinb(dj4[9]),.dout(Overflow));
	jxor xor_5_1(.dina(dj4[8]),.dinb(dj4[9]),.dout(Sum));
endmodule

