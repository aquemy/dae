(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 - person
            city0 city1 city2 city3 city4 city5 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 0.1)
         (= (citythreat city2) 5)
         (= (citythreat city3) 4.9)
         (= (citythreat city4) 10)
         (= (citythreat city5) 0)
         
; city1
         (= (timeTerre city0 city1) 16)
         (= (timeTerre city1 city0) 16)
         (= (timeTerre city5 city1) 16)
         (= (timeTerre city1 city5) 16)
         
; city2
         (= (timeTerre city0 city2) 8)
         (= (timeTerre city2 city0) 8)
         (= (timeTerre city5 city2) 8)
         (= (timeTerre city2 city5) 8)
         
; city3
         (= (timeTerre city0 city3) 4)
         (= (timeTerre city3 city0) 4)
         (= (timeTerre city5 city3) 4)
         (= (timeTerre city3 city5) 4)
         
; city4
         (= (timeTerre city0 city4) 2)
         (= (timeTerre city4 city0) 2)
         (= (timeTerre city5 city4) 2)
         (= (timeTerre city4 city5) 2)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (libre plane1)
         (libre plane2)
         
; person init
         (at person1 city0)
         (at person2 city0)
         (at person3 city0)
         
)
(:goal (and 
         (at person1 city5)
         (at person2 city5)
         (at person3 city5)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 64 0.4
; 40 10
; 16 19.6
; 12 29.8
; 8 40
