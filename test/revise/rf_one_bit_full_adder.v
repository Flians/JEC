/*

one_full_adder:
	jspl: 5
	jspl3: 1
	jnot: 6
	jdff: 10
	jor: 5
	jand: 3

Summary:
	jspl: 5
	jspl3: 1
	jnot: 6
	jdff: 10
	jor: 5
	jand: 3
*/

module one_full_adder(A, B, Carry_in, clk, Sum, Carry_out);
	input clk;
	input A;
	input B;
	input Carry_in;
	output Sum;
	output Carry_out;
	wire n6;
	wire n7;
	wire n8;
	wire n9;
	wire n10;
	wire n11;
	wire n12;
	wire n13;
	wire n14;
	wire n15;
	wire n16;
	wire n17;
	wire[1:0] w_a_0;
	wire[2:0] w_b_0;
	wire[1:0] w_fi_0;
	wire[1:0] w_n6_0;
	wire[1:0] w_n12_0;
	wire[1:0] w_n14_0;
	wire w_dff_B_6mQ14X628_0;
	wire w_dff_B_unRdHeFu7_1;
	wire w_dff_B_jFfzfZm52_1;
	wire w_dff_B_f5Smwgqt2_1;
	wire w_dff_B_IojK7XrP8_1;
	wire w_dff_A_0uPtMaDN2_0;
	wire w_dff_A_jDnUCLg46_0;
	wire w_dff_A_SkwC8TpU9_0;
	wire w_dff_A_MjoY0gCZ5_2;
	wire w_dff_A_FhrghHvL2_1;
	jor g00(.dina(w_fi_0[1]),.dinb(w_a_0[1]),.dout(n6),.clk(clk));
	jor g01(.dina(w_n6_0[1]),.dinb(w_b_0[2]),.dout(n7),.clk(clk));
	jnot g02(.din(w_n6_0[0]),.dout(n8),.clk(clk));
	jnot g03(.din(w_b_0[1]),.dout(n9),.clk(clk));
	jnot g04(.din(w_a_0[0]),.dout(n10),.clk(clk));
	jnot g05(.din(w_fi_0[0]),.dout(n11),.clk(clk));
	jor g06(.dina(n11),.dinb(n10),.dout(n12),.clk(clk));
	jand g07(.dina(w_n12_0[1]),.dinb(w_dff_B_IojK7XrP8_1),.dout(n13),.clk(clk));
	jor g08(.dina(n13),.dinb(w_dff_B_f5Smwgqt2_1),.dout(n14),.clk(clk));
	jand g09(.dina(w_n14_0[1]),.dinb(w_dff_B_jFfzfZm52_1),.dout(n15),.clk(clk));
	jnot g10(.din(w_n12_0[0]),.dout(n16),.clk(clk));
	jand g11(.dina(n16),.dinb(w_b_0[0]),.dout(n17),.clk(clk));
	jor g12(.dina(w_dff_B_6mQ14X628_0),.dinb(n15),.dout(Sum),.clk(clk));
	jnot g13(.din(w_n14_0[0]),.dout(w_dff_A_FhrghHvL2_1),.clk(clk));
	jspl jspl_w_a_0(.douta(w_a_0[0]),.doutb(w_a_0[1]),.din(A));
	jspl3 jspl3_w_b_0(.douta(w_dff_A_SkwC8TpU9_0),.doutb(w_b_0[1]),.doutc(w_dff_A_MjoY0gCZ5_2),.din(B));
	jspl jspl_w_fi_0(.douta(w_fi_0[0]),.doutb(w_fi_0[1]),.din(Carry_in));
	jspl jspl_w_n6_0(.douta(w_n6_0[0]),.doutb(w_n6_0[1]),.din(n6));
	jspl jspl_w_n12_0(.douta(w_n12_0[0]),.doutb(w_n12_0[1]),.din(n12));
	jspl jspl_w_n14_0(.douta(w_n14_0[0]),.doutb(w_n14_0[1]),.din(n14));
	jdff dff_B_6mQ14X628_0(.din(n17),.dout(w_dff_B_6mQ14X628_0),.clk(clk));
	jdff dff_B_unRdHeFu7_1(.din(n7),.dout(w_dff_B_unRdHeFu7_1),.clk(clk));
	jdff dff_B_jFfzfZm52_1(.din(w_dff_B_unRdHeFu7_1),.dout(w_dff_B_jFfzfZm52_1),.clk(clk));
	jdff dff_B_f5Smwgqt2_1(.din(n8),.dout(w_dff_B_f5Smwgqt2_1),.clk(clk));
	jdff dff_B_IojK7XrP8_1(.din(n9),.dout(w_dff_B_IojK7XrP8_1),.clk(clk));
	jdff dff_A_0uPtMaDN2_0(.dout(w_b_0[0]),.din(w_dff_A_0uPtMaDN2_0),.clk(clk));
	jdff dff_A_jDnUCLg46_0(.dout(w_dff_A_0uPtMaDN2_0),.din(w_dff_A_jDnUCLg46_0),.clk(clk));
	jdff dff_A_SkwC8TpU9_0(.dout(w_dff_A_jDnUCLg46_0),.din(w_dff_A_SkwC8TpU9_0),.clk(clk));
	jdff dff_A_MjoY0gCZ5_2(.dout(w_b_0[2]),.din(w_dff_A_MjoY0gCZ5_2),.clk(clk));
	jdff dff_A_FhrghHvL2_1(.dout(Carry_out),.din(w_dff_A_FhrghHvL2_1),.clk(clk));
endmodule

