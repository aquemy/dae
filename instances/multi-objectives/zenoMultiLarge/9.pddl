(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 person10 - person
            city0 city1 city2 city3 city4 city5 city6 city7 city8 city9 city10 city11 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 2500)
         (= (citythreat city2) 2010)
         (= (citythreat city3) 2000)
         (= (citythreat city4) 1510)
         (= (citythreat city5) 1500)
         (= (citythreat city6) 1010)
         (= (citythreat city7) 1000)
         (= (citythreat city8) 509)
         (= (citythreat city9) 500)
         (= (citythreat city10) 10)
         (= (citythreat city11) 0)
         
; city1
         (= (timeTerre city0 city1) 10)
         (= (timeTerre city1 city0) 10)
         (= (timeTerre city11 city1) 10)
         (= (timeTerre city1 city11) 10)
         (= (timeTerre city1 city2) 610)
         (= (timeTerre city1 city3) 619)
         (= (timeTerre city1 city4) 1110)
         (= (timeTerre city1 city5) 1120)
         (= (timeTerre city1 city6) 1610)
         (= (timeTerre city1 city7) 1620)
         (= (timeTerre city1 city8) 2110)
         (= (timeTerre city1 city9) 2120)
         (= (timeTerre city1 city10) 2610)
         
; city2
         (= (timeTerre city0 city2) 500)
         (= (timeTerre city2 city0) 500)
         (= (timeTerre city11 city2) 500)
         (= (timeTerre city2 city11) 500)
         (= (timeTerre city2 city1) 610)
         (= (timeTerre city2 city3) 1109)
         (= (timeTerre city2 city4) 1600)
         (= (timeTerre city2 city5) 1610)
         (= (timeTerre city2 city6) 2100)
         (= (timeTerre city2 city7) 2110)
         (= (timeTerre city2 city8) 2600)
         (= (timeTerre city2 city9) 2610)
         (= (timeTerre city2 city10) 3100)
         
; city3
         (= (timeTerre city0 city3) 509)
         (= (timeTerre city3 city0) 509)
         (= (timeTerre city11 city3) 509)
         (= (timeTerre city3 city11) 509)
         (= (timeTerre city3 city1) 619)
         (= (timeTerre city3 city2) 1109)
         (= (timeTerre city3 city4) 1609)
         (= (timeTerre city3 city5) 1619)
         (= (timeTerre city3 city6) 2109)
         (= (timeTerre city3 city7) 2119)
         (= (timeTerre city3 city8) 2609)
         (= (timeTerre city3 city9) 2619)
         (= (timeTerre city3 city10) 3109)
         
; city4
         (= (timeTerre city0 city4) 1000)
         (= (timeTerre city4 city0) 1000)
         (= (timeTerre city11 city4) 1000)
         (= (timeTerre city4 city11) 1000)
         (= (timeTerre city4 city1) 1110)
         (= (timeTerre city4 city2) 1600)
         (= (timeTerre city4 city3) 1609)
         (= (timeTerre city4 city5) 2110)
         (= (timeTerre city4 city6) 2600)
         (= (timeTerre city4 city7) 2610)
         (= (timeTerre city4 city8) 3100)
         (= (timeTerre city4 city9) 3110)
         (= (timeTerre city4 city10) 3600)
         
; city5
         (= (timeTerre city0 city5) 1010)
         (= (timeTerre city5 city0) 1010)
         (= (timeTerre city11 city5) 1010)
         (= (timeTerre city5 city11) 1010)
         (= (timeTerre city5 city1) 1120)
         (= (timeTerre city5 city2) 1610)
         (= (timeTerre city5 city3) 1619)
         (= (timeTerre city5 city4) 2110)
         (= (timeTerre city5 city6) 2610)
         (= (timeTerre city5 city7) 2620)
         (= (timeTerre city5 city8) 3110)
         (= (timeTerre city5 city9) 3120)
         (= (timeTerre city5 city10) 3610)
         
; city6
         (= (timeTerre city0 city6) 1500)
         (= (timeTerre city6 city0) 1500)
         (= (timeTerre city11 city6) 1500)
         (= (timeTerre city6 city11) 1500)
         (= (timeTerre city6 city1) 1610)
         (= (timeTerre city6 city2) 2100)
         (= (timeTerre city6 city3) 2109)
         (= (timeTerre city6 city4) 2600)
         (= (timeTerre city6 city5) 2610)
         (= (timeTerre city6 city7) 3110)
         (= (timeTerre city6 city8) 3600)
         (= (timeTerre city6 city9) 3610)
         (= (timeTerre city6 city10) 4100)
         
; city7
         (= (timeTerre city0 city7) 1510)
         (= (timeTerre city7 city0) 1510)
         (= (timeTerre city11 city7) 1510)
         (= (timeTerre city7 city11) 1510)
         (= (timeTerre city7 city1) 1620)
         (= (timeTerre city7 city2) 2110)
         (= (timeTerre city7 city3) 2119)
         (= (timeTerre city7 city4) 2610)
         (= (timeTerre city7 city5) 2620)
         (= (timeTerre city7 city6) 3110)
         (= (timeTerre city7 city8) 3610)
         (= (timeTerre city7 city9) 3620)
         (= (timeTerre city7 city10) 4110)
         
; city8
         (= (timeTerre city0 city8) 2000)
         (= (timeTerre city8 city0) 2000)
         (= (timeTerre city11 city8) 2000)
         (= (timeTerre city8 city11) 2000)
         (= (timeTerre city8 city1) 2110)
         (= (timeTerre city8 city2) 2600)
         (= (timeTerre city8 city3) 2609)
         (= (timeTerre city8 city4) 3100)
         (= (timeTerre city8 city5) 3110)
         (= (timeTerre city8 city6) 3600)
         (= (timeTerre city8 city7) 3610)
         (= (timeTerre city8 city9) 4110)
         (= (timeTerre city8 city10) 4600)
         
; city9
         (= (timeTerre city0 city9) 2010)
         (= (timeTerre city9 city0) 2010)
         (= (timeTerre city11 city9) 2010)
         (= (timeTerre city9 city11) 2010)
         (= (timeTerre city9 city1) 2120)
         (= (timeTerre city9 city2) 2610)
         (= (timeTerre city9 city3) 2619)
         (= (timeTerre city9 city4) 3110)
         (= (timeTerre city9 city5) 3120)
         (= (timeTerre city9 city6) 3610)
         (= (timeTerre city9 city7) 3620)
         (= (timeTerre city9 city8) 4110)
         (= (timeTerre city9 city10) 4610)
         
; city10
         (= (timeTerre city0 city10) 2500)
         (= (timeTerre city10 city0) 2500)
         (= (timeTerre city11 city10) 2500)
         (= (timeTerre city10 city11) 2500)
         (= (timeTerre city10 city1) 2610)
         (= (timeTerre city10 city2) 3100)
         (= (timeTerre city10 city3) 3109)
         (= (timeTerre city10 city4) 3600)
         (= (timeTerre city10 city5) 3610)
         (= (timeTerre city10 city6) 4100)
         (= (timeTerre city10 city7) 4110)
         (= (timeTerre city10 city8) 4600)
         (= (timeTerre city10 city9) 4610)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (at plane3 city0)
         (libre plane1)
         (libre plane2)
         (libre plane3)
         
; person init
         (at person1 city0)
         (at person2 city0)
         (at person3 city0)
         (at person4 city0)
         (at person5 city0)
         (at person6 city0)
         (at person7 city0)
         (at person8 city0)
         (at person9 city0)
         (at person10 city0)
         
)
(:goal (and 
         (at person1 city11)
         (at person2 city11)
         (at person3 city11)
         (at person4 city11)
         (at person5 city11)
         (at person6 city11)
         (at person7 city11)
         (at person8 city11)
         (at person9 city11)
         (at person10 city11)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 30000 170
; 29020 1150
; 29000 1168
; 28040 2130
; 28020 2148
; 28000 2166
; 27060 3110
; 27040 3128
; 27020 3146
; 27000 3164
; 26060 4110
; 26040 4128
; 26020 4146
; 26018 4150
; 26000 4166
; 25060 5110
; 25040 5128
; 25038 5130
; 25020 5146
; 25018 5148
; 25000 5166
; 24080 6580
; 24060 6598
; 24058 6600
; 24040 6616
; 24038 6618
; 24036 6630
; 24020 6636
; 24018 6645
; 24000 6663
; 23100 8050
; 23080 8068
; 23078 8070
; 23060 8086
; 23058 8088
; 23056 8099
; 23054 8100
; 23040 8106
; 23038 8115
; 23036 8127
; 23020 8133
; 23018 8142
; 23000 8160
; 22098 9540
; 22078 9558
; 22074 9570
; 22060 9576
; 22058 9585
; 22056 9596
; 22054 9597
; 22040 9603
; 22038 9612
; 22036 9618
; 22020 9630
; 22018 9639
; 22000 9659
; 21118 11010
; 21098 11028
; 21094 11040
; 21080 11046
; 21078 11055
; 21074 11067
; 21060 11073
; 21058 11082
; 21056 11088
; 21054 11094
; 21040 11100
; 21038 11109
; 21036 11115
; 21020 11129
; 21018 11136
; 21000 11156
; 20118 12500
; 20114 12510
; 20100 12518
; 20098 12527
; 20094 12537
; 20080 12545
; 20078 12554
; 20076 12558
; 20074 12564
; 20060 12572
; 20058 12581
; 20056 12585
; 20054 12591
; 20040 12599
; 20038 12606
; 20036 12612
; 20020 12626
; 20018 12633
; 20000 12656
; 19118 14000
; 19114 14009
; 19100 14018
; 19098 14027
; 19096 14029
; 19094 14036
; 19080 14045
; 19078 14054
; 19076 14056
; 19074 14063
; 19072 14070
; 19060 14072
; 19058 14076
; 19056 14083
; 19054 14090
; 19040 14099
; 19038 14103
; 19036 14110
; 19020 14128
; 19018 14132
; 19000 14158
; 18116 15500
; 18114 15509
; 18100 15518
; 18096 15527
; 18094 15536
; 18092 15540
; 18080 15545
; 18078 15546
; 18076 15554
; 18074 15563
; 18072 15567
; 18060 15572
; 18058 15573
; 18056 15581
; 18054 15588
; 18040 15599
; 18038 15602
; 18036 15608
; 18020 15628
; 18018 15629
; 18000 15658
; 17116 17000
; 17114 17009
; 17112 17010
; 17098 17018
; 17096 17027
; 17094 17036
; 17092 17037
; 17078 17045
; 17076 17054
; 17074 17059
; 17072 17064
; 17058 17072
; 17056 17081
; 17054 17086
; 17038 17099
; 17036 17106
; 17020 17128
; 17018 17129
; 17000 17159
; 16116 18500
; 16112 18509
; 16098 18518
; 16096 18527
; 16094 18529
; 16092 18536
; 16078 18545
; 16076 18554
; 16074 18556
; 16072 18563
; 16058 18572
; 16056 18576
; 16054 18583
; 16040 18599
; 16038 18601
; 16036 18605
; 16020 18629
; 16018 18631
; 16000 18661
; 15114 20000
; 15112 20009
; 15098 20018
; 15094 20027
; 15092 20036
; 15090 20040
; 15078 20045
; 15076 20046
; 15074 20054
; 15072 20064
; 15058 20072
; 15056 20075
; 15054 20081
; 15038 20101
; 15036 20102
; 15018 20131
; 15000 20161
; 14114 21500
; 14112 21509
; 14110 21510
; 14096 21518
; 14094 21527
; 14092 21536
; 14090 21537
; 14076 21545
; 14074 21554
; 14072 21559
; 14056 21572
; 14054 21583
; 14038 21601
; 14036 21602
; 14020 21631
; 14018 21632
; 14000 21662
; 13114 23000
; 13110 23009
; 13096 23018
; 13094 23027
; 13092 23029
; 13090 23036
; 13076 23045
; 13074 23054
; 13072 23056
; 13058 23072
; 13056 23074
; 13054 23078
; 13040 23101
; 13038 23102
; 13036 23104
; 13020 23132
; 13018 23133
; 13000 23163
; 12112 24500
; 12110 24509
; 12096 24518
; 12092 24527
; 12090 24537
; 12076 24545
; 12074 24548
; 12072 24554
; 12060 24572
; 12056 24574
; 12054 24575
; 12040 24602
; 12036 24604
; 12020 24633
; 12018 24634
; 12000 24664
; 11112 26000
; 11110 26009
; 11108 26010
; 11094 26018
; 11092 26027
; 11090 26037
; 11074 26045
; 11072 26056
; 11056 26074
; 11054 26075
; 11038 26104
; 11036 26105
; 11020 26134
; 11018 26135
; 11000 26165
; 10112 27500
; 10108 27509
; 10094 27518
; 10092 27527
; 10090 27529
; 10076 27545
; 10074 27547
; 10072 27556
; 10058 27574
; 10056 27575
; 10054 27577
; 10040 27604
; 10038 27605
; 10036 27606
; 10020 27635
; 10018 27636
; 10000 27666
; 9110 29000
; 9108 29010
; 9094 29018
; 9090 29027
; 9078 29045
; 9074 29047
; 9072 29048
; 9060 29074
; 9058 29075
; 9054 29077
; 9040 29105
; 9038 29106
; 9036 29107
; 9020 29136
; 9018 29137
; 9000 29167
; 8110 30500
; 8108 30510
; 8092 30518
; 8090 30529
; 8080 30545
; 8074 30547
; 8072 30548
; 8060 30575
; 8056 30577
; 8054 30578
; 8040 30606
; 8038 30607
; 8036 30608
; 8020 30637
; 8018 30638
; 8000 30668
; 7110 32000
; 7108 32010
; 7094 32018
; 7092 32020
; 7090 32029
; 7076 32047
; 7074 32048
; 7072 32050
; 7058 32077
; 7056 32078
; 7054 32079
; 7040 32107
; 7038 32108
; 7036 32109
; 7020 32138
; 7018 32139
; 7000 32169
; 6108 33500
; 6096 33518
; 6092 33520
; 6090 33529
; 6078 33547
; 6076 33548
; 6072 33550
; 6060 33577
; 6058 33578
; 6056 33579
; 6054 33580
; 6040 33608
; 6038 33609
; 6036 33610
; 6020 33639
; 6018 33640
; 6000 33670
; 5110 35000
; 5098 35018
; 5092 35020
; 5090 35038
; 5080 35047
; 5078 35048
; 5074 35050
; 5072 35070
; 5060 35078
; 5058 35079
; 5056 35080
; 5054 35100
; 5040 35109
; 5038 35110
; 5020 35140
; 5018 35518
; 5000 35520
; 4112 36500
; 4100 36518
; 4094 36520
; 4092 36540
; 4080 36548
; 4076 36550
; 4074 36570
; 4060 36579
; 4058 36580
; 4040 36610
; 4020 37000
; 4000 37018
; 3114 38000
; 3096 38020
; 3094 38040
; 3078 38050
; 3060 38080
; 3020 38500
; 3000 38520
; 2116 39500
; 2098 39520
; 2080 39550
; 2020 40000
; 2000 40020
; 1118 41000
; 1100 41020
; 1018 41500
; 1000 41520
; 120 42500
