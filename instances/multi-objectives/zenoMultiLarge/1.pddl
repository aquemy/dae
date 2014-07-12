(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 city5 city6 city7 city8 city9 city10 city11 city12 city13 city14 city15 city16 city17 city18 city19 city20 city21 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 14500)
         (= (citythreat city2) 13510)
         (= (citythreat city3) 13000)
         (= (citythreat city4) 12010)
         (= (citythreat city5) 11500)
         (= (citythreat city6) 10510)
         (= (citythreat city7) 10000)
         (= (citythreat city8) 9010)
         (= (citythreat city9) 8500)
         (= (citythreat city10) 7509)
         (= (citythreat city11) 7009)
         (= (citythreat city12) 6500)
         (= (citythreat city13) 5510)
         (= (citythreat city14) 5000)
         (= (citythreat city15) 4010)
         (= (citythreat city16) 3500)
         (= (citythreat city17) 2510)
         (= (citythreat city18) 2000)
         (= (citythreat city19) 1010)
         (= (citythreat city20) 500)
         (= (citythreat city21) 0)
         
; city1
         (= (timeTerre city0 city1) 500)
         (= (timeTerre city1 city0) 500)
         (= (timeTerre city21 city1) 500)
         (= (timeTerre city1 city21) 500)
         (= (timeTerre city1 city2) 1610)
         (= (timeTerre city1 city3) 2600)
         (= (timeTerre city1 city4) 3110)
         (= (timeTerre city1 city5) 4100)
         (= (timeTerre city1 city6) 4610)
         (= (timeTerre city1 city7) 5600)
         (= (timeTerre city1 city8) 6110)
         (= (timeTerre city1 city9) 7100)
         (= (timeTerre city1 city10) 7609)
         (= (timeTerre city1 city11) 8109)
         (= (timeTerre city1 city12) 9100)
         (= (timeTerre city1 city13) 9610)
         (= (timeTerre city1 city14) 10600)
         (= (timeTerre city1 city15) 11110)
         (= (timeTerre city1 city16) 12100)
         (= (timeTerre city1 city17) 12610)
         (= (timeTerre city1 city18) 13600)
         (= (timeTerre city1 city19) 14110)
         (= (timeTerre city1 city20) 15100)
         
; city2
         (= (timeTerre city0 city2) 1010)
         (= (timeTerre city2 city0) 1010)
         (= (timeTerre city21 city2) 1010)
         (= (timeTerre city2 city21) 1010)
         (= (timeTerre city2 city1) 1610)
         (= (timeTerre city2 city3) 3110)
         (= (timeTerre city2 city4) 3620)
         (= (timeTerre city2 city5) 4610)
         (= (timeTerre city2 city6) 5120)
         (= (timeTerre city2 city7) 6110)
         (= (timeTerre city2 city8) 6620)
         (= (timeTerre city2 city9) 7610)
         (= (timeTerre city2 city10) 8119)
         (= (timeTerre city2 city11) 8619)
         (= (timeTerre city2 city12) 9610)
         (= (timeTerre city2 city13) 10120)
         (= (timeTerre city2 city14) 11110)
         (= (timeTerre city2 city15) 11620)
         (= (timeTerre city2 city16) 12610)
         (= (timeTerre city2 city17) 13120)
         (= (timeTerre city2 city18) 14110)
         (= (timeTerre city2 city19) 14620)
         (= (timeTerre city2 city20) 15610)
         
; city3
         (= (timeTerre city0 city3) 2000)
         (= (timeTerre city3 city0) 2000)
         (= (timeTerre city21 city3) 2000)
         (= (timeTerre city3 city21) 2000)
         (= (timeTerre city3 city1) 2600)
         (= (timeTerre city3 city2) 3110)
         (= (timeTerre city3 city4) 4610)
         (= (timeTerre city3 city5) 5600)
         (= (timeTerre city3 city6) 6110)
         (= (timeTerre city3 city7) 7100)
         (= (timeTerre city3 city8) 7610)
         (= (timeTerre city3 city9) 8600)
         (= (timeTerre city3 city10) 9109)
         (= (timeTerre city3 city11) 9609)
         (= (timeTerre city3 city12) 10600)
         (= (timeTerre city3 city13) 11110)
         (= (timeTerre city3 city14) 12100)
         (= (timeTerre city3 city15) 12610)
         (= (timeTerre city3 city16) 13600)
         (= (timeTerre city3 city17) 14110)
         (= (timeTerre city3 city18) 15100)
         (= (timeTerre city3 city19) 15610)
         (= (timeTerre city3 city20) 16600)
         
; city4
         (= (timeTerre city0 city4) 2510)
         (= (timeTerre city4 city0) 2510)
         (= (timeTerre city21 city4) 2510)
         (= (timeTerre city4 city21) 2510)
         (= (timeTerre city4 city1) 3110)
         (= (timeTerre city4 city2) 3620)
         (= (timeTerre city4 city3) 4610)
         (= (timeTerre city4 city5) 6110)
         (= (timeTerre city4 city6) 6620)
         (= (timeTerre city4 city7) 7610)
         (= (timeTerre city4 city8) 8120)
         (= (timeTerre city4 city9) 9110)
         (= (timeTerre city4 city10) 9619)
         (= (timeTerre city4 city11) 10119)
         (= (timeTerre city4 city12) 11110)
         (= (timeTerre city4 city13) 11620)
         (= (timeTerre city4 city14) 12610)
         (= (timeTerre city4 city15) 13120)
         (= (timeTerre city4 city16) 14110)
         (= (timeTerre city4 city17) 14620)
         (= (timeTerre city4 city18) 15610)
         (= (timeTerre city4 city19) 16120)
         (= (timeTerre city4 city20) 17110)
         
; city5
         (= (timeTerre city0 city5) 3500)
         (= (timeTerre city5 city0) 3500)
         (= (timeTerre city21 city5) 3500)
         (= (timeTerre city5 city21) 3500)
         (= (timeTerre city5 city1) 4100)
         (= (timeTerre city5 city2) 4610)
         (= (timeTerre city5 city3) 5600)
         (= (timeTerre city5 city4) 6110)
         (= (timeTerre city5 city6) 7610)
         (= (timeTerre city5 city7) 8600)
         (= (timeTerre city5 city8) 9110)
         (= (timeTerre city5 city9) 10100)
         (= (timeTerre city5 city10) 10609)
         (= (timeTerre city5 city11) 11109)
         (= (timeTerre city5 city12) 12100)
         (= (timeTerre city5 city13) 12610)
         (= (timeTerre city5 city14) 13600)
         (= (timeTerre city5 city15) 14110)
         (= (timeTerre city5 city16) 15100)
         (= (timeTerre city5 city17) 15610)
         (= (timeTerre city5 city18) 16600)
         (= (timeTerre city5 city19) 17110)
         (= (timeTerre city5 city20) 18100)
         
; city6
         (= (timeTerre city0 city6) 4010)
         (= (timeTerre city6 city0) 4010)
         (= (timeTerre city21 city6) 4010)
         (= (timeTerre city6 city21) 4010)
         (= (timeTerre city6 city1) 4610)
         (= (timeTerre city6 city2) 5120)
         (= (timeTerre city6 city3) 6110)
         (= (timeTerre city6 city4) 6620)
         (= (timeTerre city6 city5) 7610)
         (= (timeTerre city6 city7) 9110)
         (= (timeTerre city6 city8) 9620)
         (= (timeTerre city6 city9) 10610)
         (= (timeTerre city6 city10) 11119)
         (= (timeTerre city6 city11) 11619)
         (= (timeTerre city6 city12) 12610)
         (= (timeTerre city6 city13) 13120)
         (= (timeTerre city6 city14) 14110)
         (= (timeTerre city6 city15) 14620)
         (= (timeTerre city6 city16) 15610)
         (= (timeTerre city6 city17) 16120)
         (= (timeTerre city6 city18) 17110)
         (= (timeTerre city6 city19) 17620)
         (= (timeTerre city6 city20) 18610)
         
; city7
         (= (timeTerre city0 city7) 5000)
         (= (timeTerre city7 city0) 5000)
         (= (timeTerre city21 city7) 5000)
         (= (timeTerre city7 city21) 5000)
         (= (timeTerre city7 city1) 5600)
         (= (timeTerre city7 city2) 6110)
         (= (timeTerre city7 city3) 7100)
         (= (timeTerre city7 city4) 7610)
         (= (timeTerre city7 city5) 8600)
         (= (timeTerre city7 city6) 9110)
         (= (timeTerre city7 city8) 10610)
         (= (timeTerre city7 city9) 11600)
         (= (timeTerre city7 city10) 12109)
         (= (timeTerre city7 city11) 12609)
         (= (timeTerre city7 city12) 13600)
         (= (timeTerre city7 city13) 14110)
         (= (timeTerre city7 city14) 15100)
         (= (timeTerre city7 city15) 15610)
         (= (timeTerre city7 city16) 16600)
         (= (timeTerre city7 city17) 17110)
         (= (timeTerre city7 city18) 18100)
         (= (timeTerre city7 city19) 18610)
         (= (timeTerre city7 city20) 19600)
         
; city8
         (= (timeTerre city0 city8) 5510)
         (= (timeTerre city8 city0) 5510)
         (= (timeTerre city21 city8) 5510)
         (= (timeTerre city8 city21) 5510)
         (= (timeTerre city8 city1) 6110)
         (= (timeTerre city8 city2) 6620)
         (= (timeTerre city8 city3) 7610)
         (= (timeTerre city8 city4) 8120)
         (= (timeTerre city8 city5) 9110)
         (= (timeTerre city8 city6) 9620)
         (= (timeTerre city8 city7) 10610)
         (= (timeTerre city8 city9) 12110)
         (= (timeTerre city8 city10) 12619)
         (= (timeTerre city8 city11) 13119)
         (= (timeTerre city8 city12) 14110)
         (= (timeTerre city8 city13) 14620)
         (= (timeTerre city8 city14) 15610)
         (= (timeTerre city8 city15) 16120)
         (= (timeTerre city8 city16) 17110)
         (= (timeTerre city8 city17) 17620)
         (= (timeTerre city8 city18) 18610)
         (= (timeTerre city8 city19) 19120)
         (= (timeTerre city8 city20) 20110)
         
; city9
         (= (timeTerre city0 city9) 6500)
         (= (timeTerre city9 city0) 6500)
         (= (timeTerre city21 city9) 6500)
         (= (timeTerre city9 city21) 6500)
         (= (timeTerre city9 city1) 7100)
         (= (timeTerre city9 city2) 7610)
         (= (timeTerre city9 city3) 8600)
         (= (timeTerre city9 city4) 9110)
         (= (timeTerre city9 city5) 10100)
         (= (timeTerre city9 city6) 10610)
         (= (timeTerre city9 city7) 11600)
         (= (timeTerre city9 city8) 12110)
         (= (timeTerre city9 city10) 13609)
         (= (timeTerre city9 city11) 14109)
         (= (timeTerre city9 city12) 15100)
         (= (timeTerre city9 city13) 15610)
         (= (timeTerre city9 city14) 16600)
         (= (timeTerre city9 city15) 17110)
         (= (timeTerre city9 city16) 18100)
         (= (timeTerre city9 city17) 18610)
         (= (timeTerre city9 city18) 19600)
         (= (timeTerre city9 city19) 20110)
         (= (timeTerre city9 city20) 21100)
         
; city10
         (= (timeTerre city0 city10) 7009)
         (= (timeTerre city10 city0) 7009)
         (= (timeTerre city21 city10) 7009)
         (= (timeTerre city10 city21) 7009)
         (= (timeTerre city10 city1) 7609)
         (= (timeTerre city10 city2) 8119)
         (= (timeTerre city10 city3) 9109)
         (= (timeTerre city10 city4) 9619)
         (= (timeTerre city10 city5) 10609)
         (= (timeTerre city10 city6) 11119)
         (= (timeTerre city10 city7) 12109)
         (= (timeTerre city10 city8) 12619)
         (= (timeTerre city10 city9) 13609)
         (= (timeTerre city10 city11) 14618)
         (= (timeTerre city10 city12) 15609)
         (= (timeTerre city10 city13) 16119)
         (= (timeTerre city10 city14) 17109)
         (= (timeTerre city10 city15) 17619)
         (= (timeTerre city10 city16) 18609)
         (= (timeTerre city10 city17) 19119)
         (= (timeTerre city10 city18) 20109)
         (= (timeTerre city10 city19) 20619)
         (= (timeTerre city10 city20) 21609)
         
; city11
         (= (timeTerre city0 city11) 7509)
         (= (timeTerre city11 city0) 7509)
         (= (timeTerre city21 city11) 7509)
         (= (timeTerre city11 city21) 7509)
         (= (timeTerre city11 city1) 8109)
         (= (timeTerre city11 city2) 8619)
         (= (timeTerre city11 city3) 9609)
         (= (timeTerre city11 city4) 10119)
         (= (timeTerre city11 city5) 11109)
         (= (timeTerre city11 city6) 11619)
         (= (timeTerre city11 city7) 12609)
         (= (timeTerre city11 city8) 13119)
         (= (timeTerre city11 city9) 14109)
         (= (timeTerre city11 city10) 14618)
         (= (timeTerre city11 city12) 16109)
         (= (timeTerre city11 city13) 16619)
         (= (timeTerre city11 city14) 17609)
         (= (timeTerre city11 city15) 18119)
         (= (timeTerre city11 city16) 19109)
         (= (timeTerre city11 city17) 19619)
         (= (timeTerre city11 city18) 20609)
         (= (timeTerre city11 city19) 21119)
         (= (timeTerre city11 city20) 22109)
         
; city12
         (= (timeTerre city0 city12) 8500)
         (= (timeTerre city12 city0) 8500)
         (= (timeTerre city21 city12) 8500)
         (= (timeTerre city12 city21) 8500)
         (= (timeTerre city12 city1) 9100)
         (= (timeTerre city12 city2) 9610)
         (= (timeTerre city12 city3) 10600)
         (= (timeTerre city12 city4) 11110)
         (= (timeTerre city12 city5) 12100)
         (= (timeTerre city12 city6) 12610)
         (= (timeTerre city12 city7) 13600)
         (= (timeTerre city12 city8) 14110)
         (= (timeTerre city12 city9) 15100)
         (= (timeTerre city12 city10) 15609)
         (= (timeTerre city12 city11) 16109)
         (= (timeTerre city12 city13) 17610)
         (= (timeTerre city12 city14) 18600)
         (= (timeTerre city12 city15) 19110)
         (= (timeTerre city12 city16) 20100)
         (= (timeTerre city12 city17) 20610)
         (= (timeTerre city12 city18) 21600)
         (= (timeTerre city12 city19) 22110)
         (= (timeTerre city12 city20) 23100)
         
; city13
         (= (timeTerre city0 city13) 9010)
         (= (timeTerre city13 city0) 9010)
         (= (timeTerre city21 city13) 9010)
         (= (timeTerre city13 city21) 9010)
         (= (timeTerre city13 city1) 9610)
         (= (timeTerre city13 city2) 10120)
         (= (timeTerre city13 city3) 11110)
         (= (timeTerre city13 city4) 11620)
         (= (timeTerre city13 city5) 12610)
         (= (timeTerre city13 city6) 13120)
         (= (timeTerre city13 city7) 14110)
         (= (timeTerre city13 city8) 14620)
         (= (timeTerre city13 city9) 15610)
         (= (timeTerre city13 city10) 16119)
         (= (timeTerre city13 city11) 16619)
         (= (timeTerre city13 city12) 17610)
         (= (timeTerre city13 city14) 19110)
         (= (timeTerre city13 city15) 19620)
         (= (timeTerre city13 city16) 20610)
         (= (timeTerre city13 city17) 21120)
         (= (timeTerre city13 city18) 22110)
         (= (timeTerre city13 city19) 22620)
         (= (timeTerre city13 city20) 23610)
         
; city14
         (= (timeTerre city0 city14) 10000)
         (= (timeTerre city14 city0) 10000)
         (= (timeTerre city21 city14) 10000)
         (= (timeTerre city14 city21) 10000)
         (= (timeTerre city14 city1) 10600)
         (= (timeTerre city14 city2) 11110)
         (= (timeTerre city14 city3) 12100)
         (= (timeTerre city14 city4) 12610)
         (= (timeTerre city14 city5) 13600)
         (= (timeTerre city14 city6) 14110)
         (= (timeTerre city14 city7) 15100)
         (= (timeTerre city14 city8) 15610)
         (= (timeTerre city14 city9) 16600)
         (= (timeTerre city14 city10) 17109)
         (= (timeTerre city14 city11) 17609)
         (= (timeTerre city14 city12) 18600)
         (= (timeTerre city14 city13) 19110)
         (= (timeTerre city14 city15) 20610)
         (= (timeTerre city14 city16) 21600)
         (= (timeTerre city14 city17) 22110)
         (= (timeTerre city14 city18) 23100)
         (= (timeTerre city14 city19) 23610)
         (= (timeTerre city14 city20) 24600)
         
; city15
         (= (timeTerre city0 city15) 10510)
         (= (timeTerre city15 city0) 10510)
         (= (timeTerre city21 city15) 10510)
         (= (timeTerre city15 city21) 10510)
         (= (timeTerre city15 city1) 11110)
         (= (timeTerre city15 city2) 11620)
         (= (timeTerre city15 city3) 12610)
         (= (timeTerre city15 city4) 13120)
         (= (timeTerre city15 city5) 14110)
         (= (timeTerre city15 city6) 14620)
         (= (timeTerre city15 city7) 15610)
         (= (timeTerre city15 city8) 16120)
         (= (timeTerre city15 city9) 17110)
         (= (timeTerre city15 city10) 17619)
         (= (timeTerre city15 city11) 18119)
         (= (timeTerre city15 city12) 19110)
         (= (timeTerre city15 city13) 19620)
         (= (timeTerre city15 city14) 20610)
         (= (timeTerre city15 city16) 22110)
         (= (timeTerre city15 city17) 22620)
         (= (timeTerre city15 city18) 23610)
         (= (timeTerre city15 city19) 24120)
         (= (timeTerre city15 city20) 25110)
         
; city16
         (= (timeTerre city0 city16) 11500)
         (= (timeTerre city16 city0) 11500)
         (= (timeTerre city21 city16) 11500)
         (= (timeTerre city16 city21) 11500)
         (= (timeTerre city16 city1) 12100)
         (= (timeTerre city16 city2) 12610)
         (= (timeTerre city16 city3) 13600)
         (= (timeTerre city16 city4) 14110)
         (= (timeTerre city16 city5) 15100)
         (= (timeTerre city16 city6) 15610)
         (= (timeTerre city16 city7) 16600)
         (= (timeTerre city16 city8) 17110)
         (= (timeTerre city16 city9) 18100)
         (= (timeTerre city16 city10) 18609)
         (= (timeTerre city16 city11) 19109)
         (= (timeTerre city16 city12) 20100)
         (= (timeTerre city16 city13) 20610)
         (= (timeTerre city16 city14) 21600)
         (= (timeTerre city16 city15) 22110)
         (= (timeTerre city16 city17) 23610)
         (= (timeTerre city16 city18) 24600)
         (= (timeTerre city16 city19) 25110)
         (= (timeTerre city16 city20) 26100)
         
; city17
         (= (timeTerre city0 city17) 12010)
         (= (timeTerre city17 city0) 12010)
         (= (timeTerre city21 city17) 12010)
         (= (timeTerre city17 city21) 12010)
         (= (timeTerre city17 city1) 12610)
         (= (timeTerre city17 city2) 13120)
         (= (timeTerre city17 city3) 14110)
         (= (timeTerre city17 city4) 14620)
         (= (timeTerre city17 city5) 15610)
         (= (timeTerre city17 city6) 16120)
         (= (timeTerre city17 city7) 17110)
         (= (timeTerre city17 city8) 17620)
         (= (timeTerre city17 city9) 18610)
         (= (timeTerre city17 city10) 19119)
         (= (timeTerre city17 city11) 19619)
         (= (timeTerre city17 city12) 20610)
         (= (timeTerre city17 city13) 21120)
         (= (timeTerre city17 city14) 22110)
         (= (timeTerre city17 city15) 22620)
         (= (timeTerre city17 city16) 23610)
         (= (timeTerre city17 city18) 25110)
         (= (timeTerre city17 city19) 25620)
         (= (timeTerre city17 city20) 26610)
         
; city18
         (= (timeTerre city0 city18) 13000)
         (= (timeTerre city18 city0) 13000)
         (= (timeTerre city21 city18) 13000)
         (= (timeTerre city18 city21) 13000)
         (= (timeTerre city18 city1) 13600)
         (= (timeTerre city18 city2) 14110)
         (= (timeTerre city18 city3) 15100)
         (= (timeTerre city18 city4) 15610)
         (= (timeTerre city18 city5) 16600)
         (= (timeTerre city18 city6) 17110)
         (= (timeTerre city18 city7) 18100)
         (= (timeTerre city18 city8) 18610)
         (= (timeTerre city18 city9) 19600)
         (= (timeTerre city18 city10) 20109)
         (= (timeTerre city18 city11) 20609)
         (= (timeTerre city18 city12) 21600)
         (= (timeTerre city18 city13) 22110)
         (= (timeTerre city18 city14) 23100)
         (= (timeTerre city18 city15) 23610)
         (= (timeTerre city18 city16) 24600)
         (= (timeTerre city18 city17) 25110)
         (= (timeTerre city18 city19) 26610)
         (= (timeTerre city18 city20) 27600)
         
; city19
         (= (timeTerre city0 city19) 13510)
         (= (timeTerre city19 city0) 13510)
         (= (timeTerre city21 city19) 13510)
         (= (timeTerre city19 city21) 13510)
         (= (timeTerre city19 city1) 14110)
         (= (timeTerre city19 city2) 14620)
         (= (timeTerre city19 city3) 15610)
         (= (timeTerre city19 city4) 16120)
         (= (timeTerre city19 city5) 17110)
         (= (timeTerre city19 city6) 17620)
         (= (timeTerre city19 city7) 18610)
         (= (timeTerre city19 city8) 19120)
         (= (timeTerre city19 city9) 20110)
         (= (timeTerre city19 city10) 20619)
         (= (timeTerre city19 city11) 21119)
         (= (timeTerre city19 city12) 22110)
         (= (timeTerre city19 city13) 22620)
         (= (timeTerre city19 city14) 23610)
         (= (timeTerre city19 city15) 24120)
         (= (timeTerre city19 city16) 25110)
         (= (timeTerre city19 city17) 25620)
         (= (timeTerre city19 city18) 26610)
         (= (timeTerre city19 city20) 28110)
         
; city20
         (= (timeTerre city0 city20) 14500)
         (= (timeTerre city20 city0) 14500)
         (= (timeTerre city21 city20) 14500)
         (= (timeTerre city20 city21) 14500)
         (= (timeTerre city20 city1) 15100)
         (= (timeTerre city20 city2) 15610)
         (= (timeTerre city20 city3) 16600)
         (= (timeTerre city20 city4) 17110)
         (= (timeTerre city20 city5) 18100)
         (= (timeTerre city20 city6) 18610)
         (= (timeTerre city20 city7) 19600)
         (= (timeTerre city20 city8) 20110)
         (= (timeTerre city20 city9) 21100)
         (= (timeTerre city20 city10) 21609)
         (= (timeTerre city20 city11) 22109)
         (= (timeTerre city20 city12) 23100)
         (= (timeTerre city20 city13) 23610)
         (= (timeTerre city20 city14) 24600)
         (= (timeTerre city20 city15) 25110)
         (= (timeTerre city20 city16) 26100)
         (= (timeTerre city20 city17) 26610)
         (= (timeTerre city20 city18) 27600)
         (= (timeTerre city20 city19) 28110)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (libre plane1)
         (libre plane2)
         
; person init
         (at person1 city0)
         (at person2 city0)
         (at person3 city0)
         (at person4 city0)
         (at person5 city0)
         (at person6 city0)
         
)
(:goal (and 
         (at person1 city21)
         (at person2 city21)
         (at person3 city21)
         (at person4 city21)
         (at person5 city21)
         (at person6 city21)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 145000 5000
; 143020 6020
; 141040 7040
; 139060 8060
; 137080 9080
; 135100 10100
; 134080 12080
; 132100 13100
; 131080 15080
; 129100 16100
; 128080 18080
; 126100 19100
; 126058 21058
; 125078 21078
; 124078 22078
; 123098 22098
; 122098 23098
; 122078 24078
; 121078 25078
; 120098 25098
; 119098 26098
; 119078 27078
; 118078 28078
; 117098 28098
; 116098 29098
; 116078 30078
; 115078 31078
; 114098 31098
; 113098 32098
; 113076 33076
; 113056 34056
; 112076 34076
; 111096 34096
; 111076 35076
; 110096 35096
; 110076 36076
; 110060 36089
; 109096 36096
; 109076 37076
; 108096 37096
; 108076 38076
; 107096 38096
; 107076 39076
; 107060 39089
; 106096 39096
; 106076 40076
; 105096 40096
; 105076 41076
; 104096 41096
; 104076 42076
; 104060 42089
; 103096 42096
; 103076 43076
; 102096 43096
; 102076 44076
; 101096 44096
; 101074 45074
; 101060 45089
; 100096 45096
; 100074 46074
; 99094 46094
; 99074 47074
; 98094 47094
; 98074 48074
; 98058 48087
; 97094 48094
; 97074 49074
; 97058 49087
; 96094 49094
; 96074 50074
; 95094 50094
; 95078 50597
; 95074 51074
; 95058 51087
; 94094 51094
; 94074 52074
; 94058 52087
; 93094 52094
; 93074 53074
; 92094 53094
; 92078 53597
; 92074 54074
; 92058 54087
; 91094 54094
; 91074 55074
; 91058 55087
; 90094 55094
; 90078 55597
; 90074 56074
; 89094 56094
; 89078 56597
; 89072 57072
; 89058 57087
; 88094 57094
; 88072 58072
; 88058 58087
; 87092 58092
; 87078 58597
; 87072 59072
; 86092 59092
; 86078 59597
; 86072 60072
; 86056 60085
; 85092 60092
; 85072 61072
; 85056 61085
; 84092 61092
; 84078 61597
; 84072 62072
; 84056 62085
; 83092 62092
; 83076 62595
; 83072 63072
; 83056 63085
; 83040 63089
; 82092 63092
; 82076 63595
; 82072 64072
; 82056 64085
; 81092 64092
; 81076 64597
; 81060 64599
; 81056 65085
; 80092 65092
; 80076 65595
; 80072 66072
; 80056 66085
; 80040 66089
; 79092 66092
; 79076 66595
; 79072 67072
; 79056 67085
; 78092 67092
; 78076 67595
; 78060 67599
; 78056 68085
; 77092 68092
; 77076 68595
; 77072 69072
; 77056 69085
; 77040 69089
; 76092 69092
; 76076 69595
; 76072 70072
; 76056 70085
; 75090 70090
; 75076 70595
; 75060 70599
; 75056 71085
; 74090 71090
; 74076 71595
; 74072 72072
; 74054 72083
; 74040 72089
; 73090 72090
; 73076 72595
; 73072 73072
; 73054 73083
; 72090 73090
; 72076 73595
; 72074 73596
; 72060 73599
; 72054 74083
; 71090 74090
; 71074 74593
; 71072 75072
; 71054 75083
; 71038 75087
; 70090 75090
; 70074 75593
; 70072 76072
; 70054 76083
; 70038 76087
; 69092 76092
; 69074 76593
; 69058 76597
; 69054 77083
; 68092 77092
; 68074 77593
; 68058 77597
; 68054 78083
; 68038 78087
; 67092 78092
; 67074 78593
; 67072 79072
; 67054 79083
; 67038 79087
; 66092 79092
; 66074 79593
; 66058 79597
; 66054 80083
; 65092 80092
; 65074 80593
; 65058 80597
; 65054 81083
; 65038 81087
; 64092 81092
; 64074 81593
; 64072 82072
; 64054 82083
; 64038 82087
; 63092 82092
; 63074 82593
; 63058 82597
; 63054 83083
; 62092 83092
; 62074 83595
; 62058 83597
; 62054 84083
; 62038 84087
; 61092 84092
; 61074 84595
; 61072 85072
; 61054 85084
; 61038 85087
; 60092 85092
; 60072 85594
; 60058 85597
; 60054 86084
; 59092 86092
; 59072 86594
; 59058 86597
; 59054 87084
; 59036 87085
; 58092 87092
; 58072 87593
; 58054 88084
; 58036 88085
; 57114 88093
; 57094 88094
; 57072 88593
; 57056 88595
; 57054 89084
; 57036 89085
; 56094 89094
; 56072 89593
; 56056 89595
; 56054 90084
; 56036 90085
; 55094 90094
; 55074 90594
; 55056 90595
; 55054 91084
; 55036 91085
; 54094 91094
; 54074 91594
; 54056 91595
; 54040 91599
; 54036 92085
; 53094 92094
; 53074 92594
; 53056 92595
; 53054 93084
; 53036 93085
; 52094 93094
; 52074 93594
; 52056 93595
; 52054 94084
; 52036 94085
; 51094 94094
; 51074 94594
; 51040 94599
; 51036 95085
; 50094 95094
; 50074 95594
; 50056 95596
; 50054 96084
; 50036 96086
; 49094 96094
; 49056 96596
; 49054 97084
; 49036 97086
; 48094 97094
; 48074 97595
; 48040 97599
; 48036 98086
; 47094 98094
; 47074 98595
; 47056 98596
; 47054 99085
; 47036 99086
; 46094 99094
; 46056 99596
; 46054 100085
; 46036 100086
; 45116 100095
; 45096 100096
; 45074 100595
; 45040 100599
; 45036 101086
; 44096 101096
; 44054 101595
; 43136 102095
; 43096 102096
; 43054 102595
; 43036 103086
; 42136 103095
; 42096 103096
; 42054 103595
; 42038 103597
; 42036 104086
; 41096 104096
; 41056 104596
; 41038 104597
; 40096 105096
; 40056 105596
; 40036 106086
; 39096 106096
; 39056 106596
; 39038 106598
; 39036 107086
; 38096 107096
; 38076 107596
; 38038 107598
; 37096 108096
; 37056 108597
; 37036 109087
; 36096 109096
; 36056 109597
; 36038 109598
; 36036 110087
; 35096 110096
; 35076 110597
; 35038 110598
; 34096 111096
; 34056 111597
; 34036 112087
; 33118 112097
; 33098 112587
; 33056 112597
; 33038 112598
; 33036 113087
; 32098 113098
; 32076 113597
; 32038 113598
; 31098 114098
; 31056 114597
; 31036 115087
; 30138 115097
; 30118 115098
; 30098 115588
; 30036 115597
; 29158 116097
; 29098 116098
; 29036 116597
; 28158 117097
; 28098 117098
; 28058 117598
; 28036 118087
; 27118 118098
; 27098 118588
; 27058 118598
; 27038 119088
; 27020 119090
; 26098 119098
; 26078 119598
; 26038 119599
; 25098 120098
; 25078 121078
; 25058 121088
; 25038 121089
; 24118 121098
; 24098 121588
; 24058 121599
; 24038 122089
; 24020 122090
; 23098 122098
; 23038 122599
; 22098 123098
; 22078 124078
; 22038 124089
; 21120 124099
; 21058 124599
; 21038 125089
; 21020 125090
; 20100 125589
; 20038 125599
; 19160 126099
; 19100 126100
; 19038 127089
; 18180 127100
; 18058 127599
; 18038 128089
; 18020 128090
; 17140 128589
; 17100 128590
; 17038 128599
; 16160 129099
; 16100 129100
; 16038 130089
; 16018 130579
; 15060 130600
; 14100 131590
; 13100 132100
; 13060 133090
; 12120 133600
; 12080 134080
; 11100 134590
; 10100 135100
; 10080 136570
; 9080 137080
; 9060 138070
; 8060 139060
; 8040 140050
; 7040 141040
; 7020 142030
; 6020 143020
; 6000 144010
; 5000 145000
