(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 10)
         (= (citythreat city2) 500)
         (= (citythreat city3) 509)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 509)
         (= (timeTerre city1 city0) 509)
         (= (timeTerre city4 city1) 509)
         (= (timeTerre city1 city4) 509)
         
; city2
         (= (timeTerre city0 city2) 500)
         (= (timeTerre city2 city0) 500)
         (= (timeTerre city4 city2) 500)
         (= (timeTerre city2 city4) 500)
         
; city3
         (= (timeTerre city0 city3) 10)
         (= (timeTerre city3 city0) 10)
         (= (timeTerre city4 city3) 10)
         (= (timeTerre city3 city4) 10)
         
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
; 5090 100
; 5072 1080
; 4092 1098
; 4072 1597
; 4054 2087
; 3094 2096
; 3054 2595
; 3036 3085
; 2096 3094
; 2036 3593
; 2018 4083
; 1098 4092
; 1018 4591
; 1000 5081
; 100 5090
