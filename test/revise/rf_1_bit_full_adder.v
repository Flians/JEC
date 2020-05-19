/*

add:
	jspl: 5
	jspl3: 1
	jcb: 5
	jnot: 6
	jdff: 3
	jand: 3

Summary:
	jspl: 5
	jspl3: 1
	jcb: 5
	jnot: 6
	jdff: 3
	jand: 3
*/

module autoadd(A, B, Carry_in, clk, Sum, Carry_out);
	input A;
	input B;
	input Carry_in;
	input clk;
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
	wire n18;
	wire n19;
	wire[1:0] w_a_0;
	wire[2:0] w_b_0;
	wire[1:0] w_fi_0;
	wire[1:0] w_n6_0;
	wire[1:0] w_n12_0;
	wire[1:0] w_n14_0;
	wire w_dff_ab19_1_1;
	wire w_dff_764f_1_2;
	wire w_dff_09b3_1_1;
	jcb g00(.dina(w_fi_0[1]),.dinb(w_a_0[1]),.dout(n6));
	jcb g01(.dina(w_n6_0[1]),.dinb(w_b_0[2]),.dout(n7));
	jnot g02(.din(w_n6_0[0]),.dout(n8),.clk(clk));
	jdff g14(.din(n8),.dout(n18),.clk(clk));
	jnot g03(.din(w_b_0[1]),.dout(n9),.clk(clk));
	jnot g04(.din(w_a_0[0]),.dout(n10),.clk(clk));
	jnot g05(.din(w_fi_0[0]),.dout(n11),.clk(clk));
	jcb g06(.dina(n11),.dinb(n10),.dout(n12));
	jand g07(.dina(w_n12_0[1]),.dinb(n9),.dout(n13),.clk(clk));
	jcb g08(.dina(n13),.dinb(n18),.dout(n14));
	jdff g15(.din(w_dff_09b3_1_1),.dout(n19),.clk(clk));
	jand g09(.dina(w_n14_0[1]),.dinb(n19),.dout(n15),.clk(clk));
	jnot g10(.din(w_n12_0[0]),.dout(n16),.clk(clk));
	jand g11(.dina(n16),.dinb(w_dff_764f_1_2),.dout(n17),.clk(clk));
	jcb g12(.dina(n17),.dinb(n15),.dout(Sum));
	jnot g13(.din(w_n14_0[0]),.dout(Carry_out),.clk(clk));
	jspl jspl_w_a_0(.douta(w_a_0[0]),.doutb(w_a_0[1]),.din(A));
	jspl3 jspl3_w_b_0(.douta(w_b_0[0]),.doutb(w_b_0[1]),.doutc(w_b_0[2]),.din(B));
	jspl jspl_w_fi_0(.douta(w_fi_0[0]),.doutb(w_fi_0[1]),.din(Carry_in));
	jspl jspl_w_n6_0(.douta(w_n6_0[0]),.doutb(w_n6_0[1]),.din(n6));
	jspl jspl_w_n12_0(.douta(w_n12_0[0]),.doutb(w_n12_0[1]),.din(n12));
	jspl jspl_w_n14_0(.douta(w_n14_0[0]),.doutb(w_n14_0[1]),.din(n14));
	jdff dff_ab19_1_1(.din(w_b_0[0]),.dout(w_dff_ab19_1_1),.clk(clk));
	jdff dff_764f_1_2(.din(w_dff_ab19_1_1),.dout(w_dff_764f_1_2),.clk(clk));
	jdff dff_09b3_1_1(.din(n7),.dout(w_dff_09b3_1_1),.clk(clk));
endmodule