(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 2010)
         (= (citythreat city2) 1500)
         (= (citythreat city3) 509)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 509)
         (= (timeTerre city1 city0) 509)
         (= (timeTerre city4 city1) 509)
         (= (timeTerre city1 city4) 509)
         
; city2
         (= (timeTerre city0 city2) 1500)
         (= (timeTerre city2 city0) 1500)
         (= (timeTerre city4 city2) 1500)
         (= (timeTerre city2 city4) 1500)
         
; city3
         (= (timeTerre city0 city3) 2010)
         (= (timeTerre city3 city0) 2010)
         (= (timeTerre city4 city3) 2010)
         (= (timeTerre city3 city4) 2010)
         
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
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         (at person4 city4)
         (at person5 city4)
         (at person6 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 20100 5090
; 19080 7072
; 17098 8092
; 17096 9083
; 16080 9593
; 16078 10074
; 15114 10584
; 14096 11094
; 14094 12085
; 13078 12595
; 13076 13076
; 12112 13586
; 11094 14096
; 11092 15087
; 10076 15597
; 10074 16078
; 9110 16588
; 8092 17098
; 8090 18089
; 7074 18599
; 7072 19080
; 6108 19590
; 5090 20100
