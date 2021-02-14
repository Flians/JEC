// Benchmark "c499" written by ABC on Sun May 24 21:28:11 2020

module gf_c499 ( 
    Gid0, Gid1, Gid2, Gid3, Gid4, Gid5, Gid6, Gid7, Gid8, Gid9, Gid10,
    Gid11, Gid12, Gid13, Gid14, Gid15, Gid16, Gid17, Gid18, Gid19, Gid20,
    Gid21, Gid22, Gid23, Gid24, Gid25, Gid26, Gid27, Gid28, Gid29, Gid30,
    Gid31, Gic0, Gic1, Gic2, Gic3, Gic4, Gic5, Gic6, Gic7, Gr,
    God0, God1, God2, God3, God4, God5, God6, God7, God8, God9, God10,
    God11, God12, God13, God14, God15, God16, God17, God18, God19, God20,
    God21, God22, God23, God24, God25, God26, God27, God28, God29, God30,
    God31  );
  input  Gid0, Gid1, Gid2, Gid3, Gid4, Gid5, Gid6, Gid7, Gid8, Gid9,
    Gid10, Gid11, Gid12, Gid13, Gid14, Gid15, Gid16, Gid17, Gid18, Gid19,
    Gid20, Gid21, Gid22, Gid23, Gid24, Gid25, Gid26, Gid27, Gid28, Gid29,
    Gid30, Gid31, Gic0, Gic1, Gic2, Gic3, Gic4, Gic5, Gic6, Gic7, Gr;
  output God0, God1, God2, God3, God4, God5, God6, God7, God8, God9, God10,
    God11, God12, God13, God14, God15, God16, God17, God18, God19, God20,
    God21, God22, God23, God24, God25, God26, God27, God28, God29, God30,
    God31;
  wire n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
    n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
    n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111, n112,
    n113, n114, n115, n116, n117, n118, n119, n120, n121, n122, n123, n124,
    n125, n126, n127, n128, n129, n130, n131, n132, n133, n134, n135, n136,
    n137, n138, n139, n140, n141, n142, n143, n144, n145, n146, n147, n148,
    n149, n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
    n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171, n172,
    n173, n174, n175, n176, n177, n178, n180, n182, n184, n186, n187, n188,
    n189, n190, n191, n192, n194, n196, n198, n200, n201, n202, n203, n204,
    n205, n206, n208, n210, n212, n214, n215, n217, n219, n221, n223, n224,
    n225, n226, n227, n228, n229, n230, n231, n232, n233, n234, n236, n238,
    n240, n242, n243, n244, n246, n248, n250, n252, n253, n254, n255, n257,
    n259, n261, n263, n264, n266, n268, n270;
  jxor g000(.dina(Gid12), .dinb(Gid8), .dout(n73));
  jxor g001(.dina(Gid4), .dinb(Gid0), .dout(n74));
  jxor g002(.dina(n74), .dinb(n73), .dout(n75));
  jand g003(.dina(Gr), .dinb(Gic0), .dout(n76));
  jxor g004(.dina(n76), .dinb(n75), .dout(n77));
  jxor g005(.dina(Gid19), .dinb(Gid18), .dout(n78));
  jxor g006(.dina(Gid17), .dinb(Gid16), .dout(n79));
  jxor g007(.dina(n79), .dinb(n78), .dout(n80));
  jxor g008(.dina(Gid23), .dinb(Gid22), .dout(n81));
  jxor g009(.dina(Gid21), .dinb(Gid20), .dout(n82));
  jxor g010(.dina(n82), .dinb(n81), .dout(n83));
  jxor g011(.dina(n83), .dinb(n80), .dout(n84));
  jxor g012(.dina(n84), .dinb(n77), .dout(n85));
  jxor g013(.dina(Gid31), .dinb(Gid27), .dout(n86));
  jxor g014(.dina(Gid23), .dinb(Gid19), .dout(n87));
  jxor g015(.dina(n87), .dinb(n86), .dout(n88));
  jand g016(.dina(Gr), .dinb(Gic7), .dout(n89));
  jnot g017(.din(n89), .dout(n90));
  jxor g018(.dina(n90), .dinb(n88), .dout(n91));
  jxor g019(.dina(Gid7), .dinb(Gid6), .dout(n92));
  jxor g020(.dina(Gid5), .dinb(Gid4), .dout(n93));
  jxor g021(.dina(n93), .dinb(n92), .dout(n94));
  jxor g022(.dina(Gid15), .dinb(Gid14), .dout(n95));
  jxor g023(.dina(Gid13), .dinb(Gid12), .dout(n96));
  jxor g024(.dina(n96), .dinb(n95), .dout(n97));
  jxor g025(.dina(n97), .dinb(n94), .dout(n98));
  jxor g026(.dina(n98), .dinb(n91), .dout(n99));
  jxor g027(.dina(Gid30), .dinb(Gid26), .dout(n100));
  jxor g028(.dina(Gid22), .dinb(Gid18), .dout(n101));
  jxor g029(.dina(n101), .dinb(n100), .dout(n102));
  jand g030(.dina(Gr), .dinb(Gic6), .dout(n103));
  jxor g031(.dina(n103), .dinb(n102), .dout(n104));
  jxor g032(.dina(Gid3), .dinb(Gid2), .dout(n105));
  jxor g033(.dina(Gid1), .dinb(Gid0), .dout(n106));
  jxor g034(.dina(n106), .dinb(n105), .dout(n107));
  jxor g035(.dina(Gid11), .dinb(Gid10), .dout(n108));
  jxor g036(.dina(Gid9), .dinb(Gid8), .dout(n109));
  jxor g037(.dina(n109), .dinb(n108), .dout(n110));
  jxor g038(.dina(n110), .dinb(n107), .dout(n111));
  jxor g039(.dina(n111), .dinb(n104), .dout(n112));
  jand g040(.dina(n112), .dinb(n99), .dout(n113));
  jxor g041(.dina(Gid13), .dinb(Gid9), .dout(n114));
  jxor g042(.dina(Gid5), .dinb(Gid1), .dout(n115));
  jxor g043(.dina(n115), .dinb(n114), .dout(n116));
  jand g044(.dina(Gr), .dinb(Gic1), .dout(n117));
  jxor g045(.dina(n117), .dinb(n116), .dout(n118));
  jxor g046(.dina(Gid31), .dinb(Gid30), .dout(n119));
  jxor g047(.dina(Gid29), .dinb(Gid28), .dout(n120));
  jxor g048(.dina(n120), .dinb(n119), .dout(n121));
  jxor g049(.dina(Gid27), .dinb(Gid26), .dout(n122));
  jxor g050(.dina(Gid25), .dinb(Gid24), .dout(n123));
  jxor g051(.dina(n123), .dinb(n122), .dout(n124));
  jxor g052(.dina(n124), .dinb(n121), .dout(n125));
  jxor g053(.dina(n125), .dinb(n118), .dout(n126));
  jxor g054(.dina(n126), .dinb(n85), .dout(n127));
  jand g055(.dina(Gr), .dinb(Gic3), .dout(n128));
  jnot g056(.din(n128), .dout(n129));
  jxor g057(.dina(n129), .dinb(n121), .dout(n130));
  jxor g058(.dina(Gid15), .dinb(Gid11), .dout(n131));
  jxor g059(.dina(Gid7), .dinb(Gid3), .dout(n132));
  jxor g060(.dina(n132), .dinb(n131), .dout(n133));
  jxor g061(.dina(n133), .dinb(n83), .dout(n134));
  jxor g062(.dina(n134), .dinb(n130), .dout(n135));
  jand g063(.dina(Gr), .dinb(Gic2), .dout(n136));
  jnot g064(.din(n136), .dout(n137));
  jxor g065(.dina(n137), .dinb(n124), .dout(n138));
  jxor g066(.dina(Gid14), .dinb(Gid10), .dout(n139));
  jxor g067(.dina(Gid6), .dinb(Gid2), .dout(n140));
  jxor g068(.dina(n140), .dinb(n139), .dout(n141));
  jxor g069(.dina(n141), .dinb(n80), .dout(n142));
  jxor g070(.dina(n142), .dinb(n138), .dout(n143));
  jand g071(.dina(n143), .dinb(n135), .dout(n144));
  jand g072(.dina(n144), .dinb(n127), .dout(n145));
  jxor g073(.dina(n128), .dinb(n121), .dout(n146));
  jxor g074(.dina(n134), .dinb(n146), .dout(n147));
  jxor g075(.dina(n136), .dinb(n124), .dout(n148));
  jxor g076(.dina(n142), .dinb(n148), .dout(n149));
  jxor g077(.dina(n149), .dinb(n147), .dout(n150));
  jnot g078(.din(n76), .dout(n151));
  jxor g079(.dina(n151), .dinb(n75), .dout(n152));
  jxor g080(.dina(n84), .dinb(n152), .dout(n153));
  jnot g081(.din(n117), .dout(n154));
  jxor g082(.dina(n154), .dinb(n116), .dout(n155));
  jxor g083(.dina(n125), .dinb(n155), .dout(n156));
  jand g084(.dina(n156), .dinb(n153), .dout(n157));
  jand g085(.dina(n157), .dinb(n150), .dout(n158));
  jor  g086(.dina(n158), .dinb(n145), .dout(n159));
  jxor g087(.dina(Gid28), .dinb(Gid24), .dout(n160));
  jxor g088(.dina(Gid20), .dinb(Gid16), .dout(n161));
  jxor g089(.dina(n161), .dinb(n160), .dout(n162));
  jand g090(.dina(Gr), .dinb(Gic4), .dout(n163));
  jxor g091(.dina(n163), .dinb(n162), .dout(n164));
  jxor g092(.dina(n107), .dinb(n94), .dout(n165));
  jxor g093(.dina(n165), .dinb(n164), .dout(n166));
  jxor g094(.dina(Gid29), .dinb(Gid25), .dout(n167));
  jxor g095(.dina(Gid21), .dinb(Gid17), .dout(n168));
  jxor g096(.dina(n168), .dinb(n167), .dout(n169));
  jand g097(.dina(Gr), .dinb(Gic5), .dout(n170));
  jnot g098(.din(n170), .dout(n171));
  jxor g099(.dina(n171), .dinb(n169), .dout(n172));
  jxor g100(.dina(n110), .dinb(n97), .dout(n173));
  jxor g101(.dina(n173), .dinb(n172), .dout(n174));
  jand g102(.dina(n174), .dinb(n166), .dout(n175));
  jand g103(.dina(n175), .dinb(n159), .dout(n176));
  jand g104(.dina(n176), .dinb(n113), .dout(n177));
  jand g105(.dina(n177), .dinb(n85), .dout(n178));
  jxor g106(.dina(n178), .dinb(Gid0), .dout(God0));
  jand g107(.dina(n177), .dinb(n126), .dout(n180));
  jxor g108(.dina(n180), .dinb(Gid1), .dout(God1));
  jand g109(.dina(n177), .dinb(n149), .dout(n182));
  jxor g110(.dina(n182), .dinb(Gid2), .dout(God2));
  jand g111(.dina(n177), .dinb(n147), .dout(n184));
  jxor g112(.dina(n184), .dinb(Gid3), .dout(God3));
  jxor g113(.dina(n89), .dinb(n88), .dout(n186));
  jxor g114(.dina(n98), .dinb(n186), .dout(n187));
  jnot g115(.din(n112), .dout(n188));
  jand g116(.dina(n188), .dinb(n187), .dout(n189));
  jand g117(.dina(n189), .dinb(n159), .dout(n190));
  jand g118(.dina(n190), .dinb(n175), .dout(n191));
  jand g119(.dina(n191), .dinb(n85), .dout(n192));
  jxor g120(.dina(n192), .dinb(Gid4), .dout(God4));
  jand g121(.dina(n191), .dinb(n126), .dout(n194));
  jxor g122(.dina(n194), .dinb(Gid5), .dout(God5));
  jand g123(.dina(n191), .dinb(n149), .dout(n196));
  jxor g124(.dina(n196), .dinb(Gid6), .dout(God6));
  jand g125(.dina(n191), .dinb(n147), .dout(n198));
  jxor g126(.dina(n198), .dinb(Gid7), .dout(God7));
  jnot g127(.din(n166), .dout(n200));
  jxor g128(.dina(n170), .dinb(n169), .dout(n201));
  jxor g129(.dina(n173), .dinb(n201), .dout(n202));
  jand g130(.dina(n202), .dinb(n200), .dout(n203));
  jand g131(.dina(n159), .dinb(n113), .dout(n204));
  jand g132(.dina(n204), .dinb(n203), .dout(n205));
  jand g133(.dina(n205), .dinb(n85), .dout(n206));
  jxor g134(.dina(n206), .dinb(Gid8), .dout(God8));
  jand g135(.dina(n205), .dinb(n126), .dout(n208));
  jxor g136(.dina(n208), .dinb(Gid9), .dout(God9));
  jand g137(.dina(n205), .dinb(n149), .dout(n210));
  jxor g138(.dina(n210), .dinb(Gid10), .dout(God10));
  jand g139(.dina(n205), .dinb(n147), .dout(n212));
  jxor g140(.dina(n212), .dinb(Gid11), .dout(God11));
  jand g141(.dina(n203), .dinb(n190), .dout(n214));
  jand g142(.dina(n214), .dinb(n85), .dout(n215));
  jxor g143(.dina(n215), .dinb(Gid12), .dout(God12));
  jand g144(.dina(n214), .dinb(n126), .dout(n217));
  jxor g145(.dina(n217), .dinb(Gid13), .dout(God13));
  jand g146(.dina(n214), .dinb(n149), .dout(n219));
  jxor g147(.dina(n219), .dinb(Gid14), .dout(God14));
  jand g148(.dina(n214), .dinb(n147), .dout(n221));
  jxor g149(.dina(n221), .dinb(Gid15), .dout(God15));
  jand g150(.dina(n149), .dinb(n135), .dout(n223));
  jand g151(.dina(n156), .dinb(n85), .dout(n224));
  jxor g152(.dina(n112), .dinb(n187), .dout(n225));
  jand g153(.dina(n225), .dinb(n174), .dout(n226));
  jand g154(.dina(n226), .dinb(n200), .dout(n227));
  jxor g155(.dina(n202), .dinb(n166), .dout(n228));
  jand g156(.dina(n228), .dinb(n99), .dout(n229));
  jand g157(.dina(n229), .dinb(n188), .dout(n230));
  jor  g158(.dina(n230), .dinb(n227), .dout(n231));
  jand g159(.dina(n231), .dinb(n224), .dout(n232));
  jand g160(.dina(n232), .dinb(n223), .dout(n233));
  jand g161(.dina(n233), .dinb(n166), .dout(n234));
  jxor g162(.dina(n234), .dinb(Gid16), .dout(God16));
  jand g163(.dina(n233), .dinb(n202), .dout(n236));
  jxor g164(.dina(n236), .dinb(Gid17), .dout(God17));
  jand g165(.dina(n233), .dinb(n112), .dout(n238));
  jxor g166(.dina(n238), .dinb(Gid18), .dout(God18));
  jand g167(.dina(n233), .dinb(n187), .dout(n240));
  jxor g168(.dina(n240), .dinb(Gid19), .dout(God19));
  jand g169(.dina(n143), .dinb(n147), .dout(n242));
  jand g170(.dina(n232), .dinb(n242), .dout(n243));
  jand g171(.dina(n243), .dinb(n166), .dout(n244));
  jxor g172(.dina(n244), .dinb(Gid20), .dout(God20));
  jand g173(.dina(n243), .dinb(n202), .dout(n246));
  jxor g174(.dina(n246), .dinb(Gid21), .dout(God21));
  jand g175(.dina(n243), .dinb(n112), .dout(n248));
  jxor g176(.dina(n248), .dinb(Gid22), .dout(God22));
  jand g177(.dina(n243), .dinb(n187), .dout(n250));
  jxor g178(.dina(n250), .dinb(Gid23), .dout(God23));
  jand g179(.dina(n126), .dinb(n153), .dout(n252));
  jand g180(.dina(n231), .dinb(n252), .dout(n253));
  jand g181(.dina(n253), .dinb(n223), .dout(n254));
  jand g182(.dina(n254), .dinb(n166), .dout(n255));
  jxor g183(.dina(n255), .dinb(Gid24), .dout(God24));
  jand g184(.dina(n254), .dinb(n202), .dout(n257));
  jxor g185(.dina(n257), .dinb(Gid25), .dout(God25));
  jand g186(.dina(n254), .dinb(n112), .dout(n259));
  jxor g187(.dina(n259), .dinb(Gid26), .dout(God26));
  jand g188(.dina(n254), .dinb(n187), .dout(n261));
  jxor g189(.dina(n261), .dinb(Gid27), .dout(God27));
  jand g190(.dina(n253), .dinb(n242), .dout(n263));
  jand g191(.dina(n263), .dinb(n166), .dout(n264));
  jxor g192(.dina(n264), .dinb(Gid28), .dout(God28));
  jand g193(.dina(n263), .dinb(n202), .dout(n266));
  jxor g194(.dina(n266), .dinb(Gid29), .dout(God29));
  jand g195(.dina(n263), .dinb(n112), .dout(n268));
  jxor g196(.dina(n268), .dinb(Gid30), .dout(God30));
  jand g197(.dina(n263), .dinb(n187), .dout(n270));
  jxor g198(.dina(n270), .dinb(Gid31), .dout(God31));
endmodule


