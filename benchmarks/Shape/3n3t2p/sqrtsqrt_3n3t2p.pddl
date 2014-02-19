(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1.5)
         (= (citythreat city2) 2.32843)
         (= (citythreat city3) 2.9641)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 2.9641)
         (= (timeTerre city1 city0) 2.9641)
         (= (timeTerre city4 city1) 2.9641)
         (= (timeTerre city1 city4) 2.9641)
         
; city2
         (= (timeTerre city0 city2) 2.32843)
         (= (timeTerre city2 city0) 2.32843)
         (= (timeTerre city4 city2) 2.32843)
         (= (timeTerre city2 city4) 2.32843)
         
; city3
         (= (timeTerre city0 city3) 1.5)
         (= (timeTerre city3 city0) 1.5)
         (= (timeTerre city4 city3) 1.5)
         (= (timeTerre city3 city4) 1.5)
         
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
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 11.8564 6
; 10.5851 7.65685
; 8.9282 8.9282
; 7.65685 10.5851
; 6 11.8564
