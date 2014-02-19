(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1)
         (= (citythreat city2) 2)
         (= (citythreat city3) 4)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 2.09861)
         (= (timeTerre city1 city0) 2.09861)
         (= (timeTerre city4 city1) 2.09861)
         (= (timeTerre city1 city4) 2.09861)
         
; city2
         (= (timeTerre city0 city2) 1.69315)
         (= (timeTerre city2 city0) 1.69315)
         (= (timeTerre city4 city2) 1.69315)
         (= (timeTerre city2 city4) 1.69315)
         
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
; 20.9861 10
; 20.1752 12
; 19.3643 14
; 18.5533 16
; 17.7424 18
; 16.9315 20
; 16.3561 22
; 15.5452 24
; 14.9698 26
; 14.1589 28
; 13.5835 30
; 12.7726 32
; 12.1972 34
; 11.3863 36
; 10 40
