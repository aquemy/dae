(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 - person
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
         
)
(:goal (and 
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 8.39445 4
; 7.58352 6
; 6.77259 8
; 6.19722 10
; 5.38629 12
; 4 16
