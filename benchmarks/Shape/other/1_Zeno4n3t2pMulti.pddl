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
         (= (timeTerre city0 city1) 10)
         (= (timeTerre city1 city0) 10)
         (= (timeTerre city5 city1) 10)
         (= (timeTerre city1 city5) 10)
         
; city2
         (= (timeTerre city0 city2) 4.9)
         (= (timeTerre city2 city0) 4.9)
         (= (timeTerre city5 city2) 4.9)
         (= (timeTerre city2 city5) 4.9)
         
; city3
         (= (timeTerre city0 city3) 5)
         (= (timeTerre city3 city0) 5)
         (= (timeTerre city5 city3) 5)
         (= (timeTerre city3 city5) 5)
         
; city4
         (= (timeTerre city0 city4) 0.1)
         (= (timeTerre city4 city0) 0.1)
         (= (timeTerre city5 city4) 0.1)
         (= (timeTerre city4 city5) 0.1)
         
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
; 40 0.4
; 30 10
; 29.8 10.2
; 20 19.6
; 19.8 19.8
; 19.6 20
; 10.2 29.8
; 10 30
; 0.4 40
