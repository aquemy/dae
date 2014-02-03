(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1)
         (= (citythreat city2) 2)
         (= (citythreat city3) 3)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 3)
         (= (timeTerre city1 city0) 3)
         (= (timeTerre city4 city1) 3)
         (= (timeTerre city1 city4) 3)
         
; city2
         (= (timeTerre city0 city2) 2)
         (= (timeTerre city2 city0) 2)
         (= (timeTerre city4 city2) 2)
         (= (timeTerre city2 city4) 2)
         
; city3
         (= (timeTerre city0 city3) 1)
         (= (timeTerre city3 city0) 1)
         (= (timeTerre city4 city3) 1)
         (= (timeTerre city3 city4) 1)
         
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
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 48 16
; 46 18
; 44 20
; 42 22
; 40 24
; 38 26
; 36 28
; 34 30
; 32 32
; 30 34
; 28 36
; 26 38
; 24 40
; 22 42
; 20 44
; 18 46
; 16 48
