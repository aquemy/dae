(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 person10 person11 person12 person13 person14 person15 person16 person17 person18 person19 person20 person21 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 2000)
         (= (citythreat city2) 1010)
         (= (citythreat city3) 500)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 500)
         (= (timeTerre city1 city0) 500)
         (= (timeTerre city4 city1) 500)
         (= (timeTerre city1 city4) 500)
         (= (timeTerre city1 city2) 1610)
         (= (timeTerre city1 city3) 2600)
         
; city2
         (= (timeTerre city0 city2) 1010)
         (= (timeTerre city2 city0) 1010)
         (= (timeTerre city4 city2) 1010)
         (= (timeTerre city2 city4) 1010)
         (= (timeTerre city2 city1) 1610)
         (= (timeTerre city2 city3) 3110)
         
; city3
         (= (timeTerre city0 city3) 2000)
         (= (timeTerre city3 city0) 2000)
         (= (timeTerre city4 city3) 2000)
         (= (timeTerre city3 city4) 2000)
         (= (timeTerre city3 city1) 2600)
         (= (timeTerre city3 city2) 3110)
         
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
         (at person7 city0)
         (at person8 city0)
         (at person9 city0)
         (at person10 city0)
         (at person11 city0)
         (at person12 city0)
         (at person13 city0)
         (at person14 city0)
         (at person15 city0)
         (at person16 city0)
         (at person17 city0)
         (at person18 city0)
         (at person19 city0)
         (at person20 city0)
         (at person21 city0)
         
)
(:goal (and 
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         (at person4 city4)
         (at person5 city4)
         (at person6 city4)
         (at person7 city4)
         (at person8 city4)
         (at person9 city4)
         (at person10 city4)
         (at person11 city4)
         (at person12 city4)
         (at person13 city4)
         (at person14 city4)
         (at person15 city4)
         (at person16 city4)
         (at person17 city4)
         (at person18 city4)
         (at person19 city4)
         (at person20 city4)
         (at person21 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 80000 20000
; 78020 21020
; 76040 22040
; 74060 23060
; 72080 24080
; 70100 25100
; 68120 26120
; 66140 27140
; 64160 28160
; 62180 29180
; 60200 30200
; 58220 31220
; 56240 32240
; 54260 33260
; 52280 34280
; 50300 35300
; 48320 36320
; 46340 37340
; 44360 38360
; 42380 39380
; 40400 40400
; 40380 41870
; 39380 42380
; 39360 43370
; 38360 44360
; 38340 45350
; 37340 46340
; 37320 47330
; 36320 48320
; 36300 49310
; 35300 50300
; 35280 51290
; 34280 52280
; 34260 53270
; 33260 54260
; 33240 55250
; 32240 56240
; 32220 57230
; 31220 58220
; 31200 59210
; 30200 60200
; 30180 61190
; 29180 62180
; 29160 63170
; 28160 64160
; 28140 65150
; 27140 66140
; 27120 67130
; 26120 68120
; 26100 69110
; 25100 70100
; 25080 71090
; 24080 72080
; 24060 73070
; 23060 74060
; 23040 75050
; 22040 76040
; 22020 77030
; 21020 78020
; 21000 79010
; 20000 80000
