(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 plane4 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 0.1)
         (= (citythreat city2) 5)
         (= (citythreat city3) 5.1)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 5.1)
         (= (timeTerre city1 city0) 5.1)
         (= (timeTerre city4 city1) 5.1)
         (= (timeTerre city1 city4) 5.1)
         
; city2
         (= (timeTerre city0 city2) 5)
         (= (timeTerre city2 city0) 5)
         (= (timeTerre city4 city2) 5)
         (= (timeTerre city2 city4) 5)
         
; city3
         (= (timeTerre city0 city3) 0.1)
         (= (timeTerre city3 city0) 0.1)
         (= (timeTerre city4 city3) 0.1)
         (= (timeTerre city3 city4) 0.1)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (at plane3 city0)
         (at plane4 city0)
         (libre plane1)
         (libre plane2)
         (libre plane3)
         (libre plane4)
         
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
; 20.4 0.8
; 20.2 20.4
; 10.4 20.8
; 10.2 30.8
; 10 40.6
; 0.4 40.8
