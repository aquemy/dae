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
         (= (timeTerre city0 city1) 1.38629)
         (= (timeTerre city1 city0) 1.38629)
         (= (timeTerre city5 city1) 1.38629)
         (= (timeTerre city1 city5) 1.38629)
         
; city2
         (= (timeTerre city0 city2) 1.09861)
         (= (timeTerre city2 city0) 1.09861)
         (= (timeTerre city5 city2) 1.09861)
         (= (timeTerre city2 city5) 1.09861)
         
; city3
         (= (timeTerre city0 city3) 0.693147)
         (= (timeTerre city3 city0) 0.693147)
         (= (timeTerre city5 city3) 0.693147)
         (= (timeTerre city3 city5) 0.693147)
         
; city4
         (= (timeTerre city0 city4) 0)
         (= (timeTerre city4 city0) 0)
         (= (timeTerre city5 city4) 0)
         (= (timeTerre city4 city5) 0)
         
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
; 5.54518 0.4
; 4.15888 10
; 2.77259 19.6
; 1.38629 29.8
; 0 40
