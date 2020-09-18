// Benchmark "add" written by ABC on Fri Nov 29 16:14:13 2019

module one_full_adder ( 
    A, B, Carry_in,
    Sum, Carry_out  );
  input  A, B, Carry_in;
  output Sum, Carry_out;
  wire n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16, n17;
  jcb  g00(.dina(Carry_in), .dinb(A), .dout(n6));
  jcb  g01(.dina(n6), .dinb(B), .dout(n7));
  jnot g02(.din(n6), .dout(n8));
  jnot g03(.din(B), .dout(n9));
  jnot g04(.din(A), .dout(n10));
  jnot g05(.din(Carry_in), .dout(n11));
  jcb  g06(.dina(n11), .dinb(n10), .dout(n12));
  jand g07(.dina(n12), .dinb(n9), .dout(n13));
  jcb  g08(.dina(n13), .dinb(n8), .dout(n14));
  jand g09(.dina(n14), .dinb(n7), .dout(n15));
  jnot g10(.din(n12), .dout(n16));
  jand g11(.dina(n16), .dinb(B), .dout(n17));
  jcb  g12(.dina(n17), .dinb(n15), .dout(Sum));
  jnot g13(.din(n14), .dout(Carry_out));
endmodule


