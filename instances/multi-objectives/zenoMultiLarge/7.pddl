(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 plane4 plane5 plane6 plane7 plane8 plane9 plane10 plane11 plane12 plane13 plane14 plane15 plane16 plane17 plane18 plane19 plane20 plane21 plane22 plane23 plane24 plane25 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 person10 person11 person12 person13 person14 person15 person16 person17 person18 person19 person20 person21 person22 person23 person24 person25 person26 - person
            city0 city1 city2 city3 city4 city5 city6 city7 city8 city9 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 282)
         (= (citythreat city2) 264)
         (= (citythreat city3) 244)
         (= (citythreat city4) 223)
         (= (citythreat city5) 200)
         (= (citythreat city6) 173)
         (= (citythreat city7) 141)
         (= (citythreat city8) 100)
         (= (citythreat city9) 0)
         
; city1
         (= (timeTerre city0 city1) 100)
         (= (timeTerre city1 city0) 100)
         (= (timeTerre city9 city1) 100)
         (= (timeTerre city1 city9) 100)
         (= (timeTerre city1 city2) 400)
         (= (timeTerre city1 city3) 500)
         (= (timeTerre city1 city4) 600)
         (= (timeTerre city1 city5) 700)
         (= (timeTerre city1 city6) 800)
         (= (timeTerre city1 city7) 900)
         (= (timeTerre city1 city8) 1000)
         
; city2
         (= (timeTerre city0 city2) 200)
         (= (timeTerre city2 city0) 200)
         (= (timeTerre city9 city2) 200)
         (= (timeTerre city2 city9) 200)
         (= (timeTerre city2 city1) 400)
         (= (timeTerre city2 city3) 600)
         (= (timeTerre city2 city4) 700)
         (= (timeTerre city2 city5) 800)
         (= (timeTerre city2 city6) 900)
         (= (timeTerre city2 city7) 1000)
         (= (timeTerre city2 city8) 1100)
         
; city3
         (= (timeTerre city0 city3) 300)
         (= (timeTerre city3 city0) 300)
         (= (timeTerre city9 city3) 300)
         (= (timeTerre city3 city9) 300)
         (= (timeTerre city3 city1) 500)
         (= (timeTerre city3 city2) 600)
         (= (timeTerre city3 city4) 800)
         (= (timeTerre city3 city5) 900)
         (= (timeTerre city3 city6) 1000)
         (= (timeTerre city3 city7) 1100)
         (= (timeTerre city3 city8) 1200)
         
; city4
         (= (timeTerre city0 city4) 400)
         (= (timeTerre city4 city0) 400)
         (= (timeTerre city9 city4) 400)
         (= (timeTerre city4 city9) 400)
         (= (timeTerre city4 city1) 600)
         (= (timeTerre city4 city2) 700)
         (= (timeTerre city4 city3) 800)
         (= (timeTerre city4 city5) 1000)
         (= (timeTerre city4 city6) 1100)
         (= (timeTerre city4 city7) 1200)
         (= (timeTerre city4 city8) 1300)
         
; city5
         (= (timeTerre city0 city5) 500)
         (= (timeTerre city5 city0) 500)
         (= (timeTerre city9 city5) 500)
         (= (timeTerre city5 city9) 500)
         (= (timeTerre city5 city1) 700)
         (= (timeTerre city5 city2) 800)
         (= (timeTerre city5 city3) 900)
         (= (timeTerre city5 city4) 1000)
         (= (timeTerre city5 city6) 1200)
         (= (timeTerre city5 city7) 1300)
         (= (timeTerre city5 city8) 1400)
         
; city6
         (= (timeTerre city0 city6) 600)
         (= (timeTerre city6 city0) 600)
         (= (timeTerre city9 city6) 600)
         (= (timeTerre city6 city9) 600)
         (= (timeTerre city6 city1) 800)
         (= (timeTerre city6 city2) 900)
         (= (timeTerre city6 city3) 1000)
         (= (timeTerre city6 city4) 1100)
         (= (timeTerre city6 city5) 1200)
         (= (timeTerre city6 city7) 1400)
         (= (timeTerre city6 city8) 1500)
         
; city7
         (= (timeTerre city0 city7) 700)
         (= (timeTerre city7 city0) 700)
         (= (timeTerre city9 city7) 700)
         (= (timeTerre city7 city9) 700)
         (= (timeTerre city7 city1) 900)
         (= (timeTerre city7 city2) 1000)
         (= (timeTerre city7 city3) 1100)
         (= (timeTerre city7 city4) 1200)
         (= (timeTerre city7 city5) 1300)
         (= (timeTerre city7 city6) 1400)
         (= (timeTerre city7 city8) 1600)
         
; city8
         (= (timeTerre city0 city8) 800)
         (= (timeTerre city8 city0) 800)
         (= (timeTerre city9 city8) 800)
         (= (timeTerre city8 city9) 800)
         (= (timeTerre city8 city1) 1000)
         (= (timeTerre city8 city2) 1100)
         (= (timeTerre city8 city3) 1200)
         (= (timeTerre city8 city4) 1300)
         (= (timeTerre city8 city5) 1400)
         (= (timeTerre city8 city6) 1500)
         (= (timeTerre city8 city7) 1600)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (at plane3 city0)
         (at plane4 city0)
         (at plane5 city0)
         (at plane6 city0)
         (at plane7 city0)
         (at plane8 city0)
         (at plane9 city0)
         (at plane10 city0)
         (at plane11 city0)
         (at plane12 city0)
         (at plane13 city0)
         (at plane14 city0)
         (at plane15 city0)
         (at plane16 city0)
         (at plane17 city0)
         (at plane18 city0)
         (at plane19 city0)
         (at plane20 city0)
         (at plane21 city0)
         (at plane22 city0)
         (at plane23 city0)
         (at plane24 city0)
         (at plane25 city0)
         (libre plane1)
         (libre plane2)
         (libre plane3)
         (libre plane4)
         (libre plane5)
         (libre plane6)
         (libre plane7)
         (libre plane8)
         (libre plane9)
         (libre plane10)
         (libre plane11)
         (libre plane12)
         (libre plane13)
         (libre plane14)
         (libre plane15)
         (libre plane16)
         (libre plane17)
         (libre plane18)
         (libre plane19)
         (libre plane20)
         (libre plane21)
         (libre plane22)
         (libre plane23)
         (libre plane24)
         (libre plane25)
         
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
         (at person22 city0)
         (at person23 city0)
         (at person24 city0)
         (at person25 city0)
         (at person26 city0)
         
)
(:goal (and 
         (at person1 city9)
         (at person2 city9)
         (at person3 city9)
         (at person4 city9)
         (at person5 city9)
         (at person6 city9)
         (at person7 city9)
         (at person8 city9)
         (at person9 city9)
         (at person10 city9)
         (at person11 city9)
         (at person12 city9)
         (at person13 city9)
         (at person14 city9)
         (at person15 city9)
         (at person16 city9)
         (at person17 city9)
         (at person18 city9)
         (at person19 city9)
         (at person20 city9)
         (at person21 city9)
         (at person22 city9)
         (at person23 city9)
         (at person24 city9)
         (at person25 city9)
         (at person26 city9)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 3200 2700
; 3000 2782
; 2800 2846
; 2600 2900
; 2400 2946
; 2200 2988
; 2000 3028
; 1800 3064
; 1600 3137
; 1400 4148
; 1200 4939
; 1000 5608
; 800 6180
; 600 6702
; 400 7200
