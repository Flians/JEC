/*
alu_4_no_jp_clk:
	jxor: 16
	jspl: 32
	jspl3: 9
	jcb: 12
	jdff: 57
	jand: 30
	jandf: 1
	jor: 1
Summary:
	jxor: 16
	jspl: 32
	jspl3: 9
	jcb: 12
	jdff: 57
	jand: 30
	jandf: 1
	jor: 1
The maximum logic level gap of any gate:
	gf_alu_4_jandf: 0
*/
`timescale  1ps  /  100fs
module gf_alu_4_jandf(clk, X, Y, Carry_in, End_bar, Cmpl_X, Cmpl_Y, Op_XOR, Op_AND, Op_ARITH, Z, Carry_out);
	input clk;
	input[3:0] X;
	input[3:0] Y;
	input Carry_in;
	input End_bar;
	input Cmpl_X;
	input Cmpl_Y;
	input Op_XOR;
	input Op_AND;
	input Op_ARITH;
	output[3:0] Z;
	output Carry_out;
	wire [28:0] ds0;
	wire [4:0] dj0;
	wire [38:0] ds1;
	wire [7:0] dj1;
	wire [33:0] ds2;
	wire [17:0] dj2;
	wire [26:0] ds3;
	wire [49:0] dj3;
	wire [23:0] ds4;
	wire [41:0] dj4;
	wire [14:0] ds5;
	wire [64:0] dj5;
	wire [27:0] ds6;
	wire [15:0] dj6;
	wire [2:0] w_Cmpl_X_1;
	wire [1:0] w_Cmpl_X_2;
	wire [2:0] w_Cmpl_Y_1;
	wire [1:0] w_Cmpl_Y_2;
	jdff dff_0_0(.din(Carry_in),.dout(dj0[0]),.clk(clk));
	jdff dff_0_1(.din(End_bar),.dout(dj0[1]),.clk(clk));
	jxor xor_0_0(.dina(Y[3]),.dinb(w_Cmpl_Y_1[0]),.dout(ds0[2]),.clk(clk));
	jspl spl_0_0(.din(ds0[2]),.douta(ds0[3]),.doutb(ds0[4]));
	jxor xor_0_1(.dina(X[3]),.dinb(w_Cmpl_X_1[0]),.dout(ds0[5]),.clk(clk));
	jspl spl_0_1(.din(ds0[5]),.douta(ds0[6]),.doutb(ds0[7]));
	jxor xor_0_2(.dina(Y[2]),.dinb(w_Cmpl_Y_1[1]),.dout(ds0[8]),.clk(clk));
	jspl spl_0_2(.din(ds0[8]),.douta(ds0[9]),.doutb(ds0[10]));
	jxor xor_0_3(.dina(X[2]),.dinb(w_Cmpl_X_1[1]),.dout(ds0[11]),.clk(clk));
	jspl spl_0_3(.din(ds0[11]),.douta(ds0[12]),.doutb(ds0[13]));
	jxor xor_0_4(.dina(Y[1]),.dinb(w_Cmpl_Y_1[2]),.dout(ds0[14]),.clk(clk));
	jspl spl_0_4(.din(ds0[14]),.douta(ds0[15]),.doutb(ds0[16]));
	jxor xor_0_5(.dina(X[1]),.dinb(w_Cmpl_X_1[2]),.dout(ds0[17]),.clk(clk));
	jspl spl_0_5(.din(ds0[17]),.douta(ds0[18]),.doutb(ds0[19]));
	jxor xor_0_6(.dina(Y[0]),.dinb(w_Cmpl_Y_2[0]),.dout(ds0[20]),.clk(clk));
	jspl spl_0_6(.din(ds0[20]),.douta(ds0[21]),.doutb(ds0[22]));
	jxor xor_0_7(.dina(X[0]),.dinb(w_Cmpl_X_2[0]),.dout(ds0[23]),.clk(clk));
	jspl spl_0_7(.din(ds0[23]),.douta(ds0[24]),.doutb(ds0[25]));
	jdff dff_0_2(.din(Op_XOR),.dout(dj0[2]),.clk(clk));
	jdff dff_0_3(.din(Op_AND),.dout(dj0[3]),.clk(clk));
	jdff dff_0_4(.din(Op_ARITH),.dout(dj0[4]),.clk(clk));
	jdff dff_1_0(.din(dj0[0]),.dout(dj1[0]),.clk(clk));
	jdff dff_1_1(.din(dj0[1]),.dout(dj1[2]),.clk(clk));
	jand and_1_0(.dina(ds0[3]),.dinb(ds0[6]),.dout(ds1[2]),.clk(clk));
	jspl spl_1_0(.din(ds1[2]),.douta(ds1[3]),.doutb(ds1[4]));
	jxor xor_1_0(.dina(ds0[4]),.dinb(ds0[7]),.dout(dj1[4]),.clk(clk));
	jand and_1_1(.dina(ds0[9]),.dinb(ds0[12]),.dout(ds1[6]),.clk(clk));
	jspl spl_1_1(.din(ds1[6]),.douta(ds1[7]),.doutb(ds1[8]));
	jxor xor_1_1(.dina(ds0[10]),.dinb(ds0[13]),.dout(dj1[5]),.clk(clk));
	jand and_1_2(.dina(ds0[15]),.dinb(ds0[18]),.dout(ds1[10]),.clk(clk));
	jspl spl_1_2(.din(ds1[10]),.douta(ds1[11]),.doutb(ds1[12]));
	jxor xor_1_2(.dina(ds0[16]),.dinb(ds0[19]),.dout(dj1[6]),.clk(clk));
	jand and_1_3(.dina(ds0[21]),.dinb(ds0[24]),.dout(ds1[14]),.clk(clk));
	jspl spl_1_3(.din(ds1[14]),.douta(ds1[15]),.doutb(ds1[16]));
	jxor xor_1_3(.dina(ds0[22]),.dinb(ds0[25]),.dout(dj1[7]),.clk(clk));
	jdff dff_1_2(.din(dj0[2]),.dout(ds1[18]),.clk(clk));
	jspl spl_1_4(.din(ds1[18]),.douta(ds1[33]),.doutb(ds1[34]));
	jspl spl_1_5(.din(ds1[33]),.douta(ds1[19]),.doutb(ds1[20]));
	jspl spl_1_6(.din(ds1[34]),.douta(ds1[21]),.doutb(ds1[22]));
	jdff dff_1_3(.din(dj0[3]),.dout(ds1[23]),.clk(clk));
	jspl spl_1_7(.din(ds1[23]),.douta(ds1[35]),.doutb(ds1[36]));
	jspl spl_1_8(.din(ds1[35]),.douta(ds1[24]),.doutb(ds1[25]));
	jspl spl_1_9(.din(ds1[36]),.douta(ds1[26]),.doutb(ds1[27]));
	jdff dff_1_4(.din(dj0[4]),.dout(ds1[28]),.clk(clk));
	jspl spl_1_10(.din(ds1[28]),.douta(ds1[37]),.doutb(ds1[38]));
	jspl spl_1_11(.din(ds1[37]),.douta(ds1[29]),.doutb(ds1[30]));
	jspl spl_1_12(.din(ds1[38]),.douta(ds1[31]),.doutb(ds1[32]));
	jdff dff_2_0(.din(dj1[0]),.dout(dj2[0]),.clk(clk));
	jdff dff_2_1(.din(dj1[2]),.dout(dj2[4]),.clk(clk));
	jand and_2_0(.dina(ds1[3]),.dinb(ds1[32]),.dout(dj2[8]),.clk(clk));
	jand and_2_1(.dina(ds1[4]),.dinb(ds1[27]),.dout(ds2[3]),.clk(clk));
	jand and_2_2(.dina(dj1[4]),.dinb(ds1[22]),.dout(ds2[4]),.clk(clk));
	jcb cb_2_0(.dina(ds2[3]),.dinb(ds2[4]),.dout(ds2[5]));
	jspl3 spl3_2_0(.din(ds2[5]),.douta(ds2[6]),.doutb(ds2[7]),.doutc(ds2[8]));
	jand and_2_3(.dina(ds1[7]),.dinb(ds1[31]),.dout(dj2[11]),.clk(clk));
	jspl spl_2_0(.din(dj2[11]),.douta(ds2[10]),.doutb(ds2[11]));
	jand and_2_4(.dina(ds1[8]),.dinb(ds1[26]),.dout(ds2[12]),.clk(clk));
	jand and_2_5(.dina(dj1[5]),.dinb(ds1[21]),.dout(ds2[13]),.clk(clk));
	jcb cb_2_1(.dina(ds2[12]),.dinb(ds2[13]),.dout(ds2[14]));
	jspl3 spl3_2_1(.din(ds2[14]),.douta(ds2[15]),.doutb(ds2[16]),.doutc(ds2[17]));
	jand and_2_6(.dina(ds1[11]),.dinb(ds1[30]),.dout(dj2[13]),.clk(clk));
	jand and_2_7(.dina(ds1[12]),.dinb(ds1[25]),.dout(ds2[19]),.clk(clk));
	jand and_2_8(.dina(dj1[6]),.dinb(ds1[20]),.dout(ds2[20]),.clk(clk));
	jcb cb_2_2(.dina(ds2[19]),.dinb(ds2[20]),.dout(ds2[21]));
	jspl3 spl3_2_2(.din(ds2[21]),.douta(ds2[22]),.doutb(ds2[23]),.doutc(ds2[24]));
	jand and_2_9(.dina(ds1[15]),.dinb(ds1[29]),.dout(dj2[16]),.clk(clk));
	jspl spl_2_1(.din(dj2[16]),.douta(ds2[26]),.doutb(ds2[27]));
	jand and_2_10(.dina(ds1[16]),.dinb(ds1[24]),.dout(ds2[28]),.clk(clk));
	jand and_2_11(.dina(dj1[7]),.dinb(ds1[19]),.dout(ds2[29]),.clk(clk));
	jcb cb_2_3(.dina(ds2[28]),.dinb(ds2[29]),.dout(ds2[30]));
	jspl3 spl3_2_3(.din(ds2[30]),.douta(ds2[31]),.doutb(ds2[32]),.doutc(ds2[33]));
	jdff dff_3_0(.din(dj2[0]),.dout(dj3[0]),.clk(clk));
	jdff dff_3_1(.din(dj2[4]),.dout(dj3[4]),.clk(clk));
	jdff dff_3_2(.din(dj2[8]),.dout(dj3[8]),.clk(clk));
	jand and_3_0(.dina(ds2[8]),.dinb(ds2[11]),.dout(dj3[12]),.clk(clk));
	jand and_3_1(.dina(ds2[7]),.dinb(ds2[17]),.dout(dj3[15]),.clk(clk));
	jspl spl_3_0(.din(dj3[15]),.douta(ds3[5]),.doutb(ds3[6]));
	jdff dff_3_3(.din(ds2[6]),.dout(dj3[17]),.clk(clk));
	jdff dff_3_4(.din(ds2[10]),.dout(dj3[21]),.clk(clk));
	jdff dff_3_5(.din(ds2[16]),.dout(dj3[25]),.clk(clk));
	jspl spl_3_1(.din(dj3[25]),.douta(ds3[10]),.doutb(ds3[11]));
	jdff dff_3_6(.din(ds2[15]),.dout(dj3[28]),.clk(clk));
	jdff dff_3_7(.din(dj2[13]),.dout(ds3[13]),.clk(clk));
	jand and_3_2(.dina(ds2[24]),.dinb(ds2[27]),.dout(ds3[14]),.clk(clk));
	jcb cb_3_0(.dina(ds3[13]),.dinb(ds3[14]),.dout(ds3[15]));
	jspl3 spl3_3_0(.din(ds3[15]),.douta(ds3[16]),.doutb(ds3[17]),.doutc(ds3[18]));
	jand and_3_3(.dina(ds2[23]),.dinb(ds2[33]),.dout(dj3[32]),.clk(clk));
	jspl3 spl3_3_1(.din(dj3[32]),.douta(ds3[20]),.doutb(ds3[21]),.doutc(ds3[22]));
	jdff dff_3_8(.din(ds2[22]),.dout(dj3[34]),.clk(clk));
	jdff dff_3_9(.din(ds2[26]),.dout(dj3[38]),.clk(clk));
	jdff dff_3_10(.din(ds2[32]),.dout(dj3[42]),.clk(clk));
	jdff dff_3_11(.din(ds2[31]),.dout(dj3[46]),.clk(clk));
	jdff dff_4_10(.din(dj3[0]),.dout(ds4[0]),.clk(clk));
	jdff dff_4_0(.din(dj3[4]),.dout(dj4[0]),.clk(clk));
	jspl spl_4_0(.din(dj4[0]),.douta(ds4[2]),.doutb(ds4[3]));
	jor or_4_0(.dina(dj3[8]),.dinb(dj3[12]),.dout(ds4[4]),.clk(clk));
	jand and_4_0(.dina(ds3[6]),.dinb(ds3[18]),.dout(ds4[5]),.clk(clk));
	jcb cb_4_0(.dina(ds4[4]),.dinb(ds4[5]),.dout(ds4[6]));
	jspl spl_4_1(.din(ds4[6]),.douta(ds4[7]),.doutb(ds4[8]));
	jand and_4_1(.dina(ds3[5]),.dinb(ds3[22]),.dout(dj4[3]),.clk(clk));
	jspl spl_4_2(.din(dj4[3]),.douta(ds4[10]),.doutb(ds4[11]));
	jdff dff_4_1(.din(dj3[17]),.dout(dj4[5]),.clk(clk));
	jdff dff_4_2(.din(dj3[21]),.dout(ds4[13]),.clk(clk));
	jand and_4_2(.dina(ds3[11]),.dinb(ds3[17]),.dout(ds4[14]),.clk(clk));
	jcb cb_4_1(.dina(ds4[13]),.dinb(ds4[14]),.dout(dj4[9]));
	jand and_4_3(.dina(ds3[10]),.dinb(ds3[21]),.dout(dj4[10]),.clk(clk));
	jdff dff_4_3(.din(dj3[28]),.dout(dj4[13]),.clk(clk));
	jdff dff_4_4(.din(ds3[16]),.dout(dj4[17]),.clk(clk));
	jdff dff_4_5(.din(ds3[20]),.dout(dj4[21]),.clk(clk));
	jdff dff_4_6(.din(dj3[34]),.dout(dj4[25]),.clk(clk));
	jdff dff_4_7(.din(dj3[38]),.dout(dj4[29]),.clk(clk));
	jdff dff_4_8(.din(dj3[42]),.dout(dj4[33]),.clk(clk));
	jdff dff_4_9(.din(dj3[46]),.dout(dj4[37]),.clk(clk));
	jand and_5_0(.dina(ds4[2]),.dinb(ds4[8]),.dout(ds5[0]),.clk(clk));
	jcb cb_5_0(.dina(ds4[0]),.dinb(ds5[0]),.dout(ds5[1]));
	jand and_5_1(.dina(ds4[3]),.dinb(ds4[11]),.dout(dj5[2]),.clk(clk));
	jdff dff_5_0(.din(ds4[7]),.dout(dj5[7]),.clk(clk));
	jdff dff_5_1(.din(ds4[10]),.dout(dj5[12]),.clk(clk));
	jdff dff_5_2(.din(dj4[5]),.dout(dj5[17]),.clk(clk));
	jdff dff_5_3(.din(dj4[9]),.dout(dj5[22]),.clk(clk));
	jdff dff_5_4(.din(dj4[10]),.dout(dj5[27]),.clk(clk));
	jdff dff_5_5(.din(dj4[13]),.dout(dj5[32]),.clk(clk));
	jdff dff_5_6(.din(dj4[17]),.dout(dj5[37]),.clk(clk));
	jdff dff_5_7(.din(dj4[21]),.dout(dj5[42]),.clk(clk));
	jdff dff_5_8(.din(dj4[25]),.dout(dj5[47]),.clk(clk));
	jdff dff_5_9(.din(dj4[29]),.dout(dj5[52]),.clk(clk));
	jdff dff_5_10(.din(dj4[33]),.dout(dj5[57]),.clk(clk));
	jdff dff_5_11(.din(dj4[37]),.dout(dj5[62]),.clk(clk));
	jandf andf_6_0(.dina(ds5[1]), .dinb(dj5[2]), .dout(ds6[2]), .clk(clk));
	jspl spl_6_0(.din(ds6[2]),.douta(ds6[26]),.doutb(ds6[27]));
	jspl spl_6_1(.din(ds6[26]),.douta(ds6[4]),.doutb(ds6[5]));
	jspl3 spl3_6_1(.din(ds6[27]),.douta(ds6[6]),.doutb(ds6[7]),.doutc(ds6[8]));
	jdff dff_6_1(.din(dj5[7]),.dout(ds6[9]),.clk(clk));
	jand and_6_1(.dina(dj5[12]),.dinb(ds6[4]),.dout(ds6[10]),.clk(clk));
	jcb cb_6_1(.dina(ds6[9]),.dinb(ds6[10]),.dout(ds6[11]));
	jdff dff_6_2(.din(dj5[17]),.dout(dj6[0]),.clk(clk));
	jdff dff_6_3(.din(dj5[22]),.dout(ds6[13]),.clk(clk));
	jand and_6_2(.dina(dj5[27]),.dinb(ds6[5]),.dout(ds6[14]),.clk(clk));
	jcb cb_6_2(.dina(ds6[13]),.dinb(ds6[14]),.dout(ds6[15]));
	jdff dff_6_4(.din(dj5[32]),.dout(dj6[3]),.clk(clk));
	jdff dff_6_5(.din(dj5[37]),.dout(ds6[17]),.clk(clk));
	jand and_6_3(.dina(dj5[42]),.dinb(ds6[6]),.dout(ds6[18]),.clk(clk));
	jcb cb_6_3(.dina(ds6[17]),.dinb(ds6[18]),.dout(ds6[19]));
	jdff dff_6_6(.din(dj5[47]),.dout(dj6[6]),.clk(clk));
	jdff dff_6_7(.din(dj5[52]),.dout(ds6[21]),.clk(clk));
	jand and_6_4(.dina(dj5[57]),.dinb(ds6[7]),.dout(ds6[22]),.clk(clk));
	jcb cb_6_4(.dina(ds6[21]),.dinb(ds6[22]),.dout(ds6[23]));
	jdff dff_6_8(.din(dj5[62]),.dout(dj6[9]),.clk(clk));
	jdff dff_6_9(.din(ds6[8]),.dout(dj6[12]),.clk(clk));
	jdff dff_7_0(.din(ds6[11]),.dout(Carry_out),.clk(clk));
	jxor xor_7_0(.dina(dj6[0]),.dinb(ds6[15]),.dout(Z[3]),.clk(clk));
	jxor xor_7_1(.dina(dj6[3]),.dinb(ds6[19]),.dout(Z[2]),.clk(clk));
	jxor xor_7_2(.dina(dj6[6]),.dinb(ds6[23]),.dout(Z[1]),.clk(clk));
	jxor xor_7_3(.dina(dj6[9]),.dinb(dj6[12]),.dout(Z[0]),.clk(clk));
	jspl3 jspl3_w_Cmpl_X_1(.din(w_Cmpl_X_2[1]),.douta(w_Cmpl_X_1[0]),.doutb(w_Cmpl_X_1[1]),.doutc(w_Cmpl_X_1[2]));
	jspl jspl_w_Cmpl_X_2(.din(Cmpl_X),.douta(w_Cmpl_X_2[0]),.doutb(w_Cmpl_X_2[1]));
	jspl3 jspl3_w_Cmpl_Y_1(.din(w_Cmpl_Y_2[1]),.douta(w_Cmpl_Y_1[0]),.doutb(w_Cmpl_Y_1[1]),.doutc(w_Cmpl_Y_1[2]));
	jspl jspl_w_Cmpl_Y_2(.din(Cmpl_Y),.douta(w_Cmpl_Y_2[0]),.doutb(w_Cmpl_Y_2[1]));
endmodule