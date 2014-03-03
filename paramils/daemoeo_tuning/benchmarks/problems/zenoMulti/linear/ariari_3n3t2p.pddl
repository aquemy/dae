(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 300)
         (= (citythreat city2) 200)
         (= (citythreat city3) 100)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 200)
         (= (timeTerre city1 city0) 200)
         (= (timeTerre city4 city1) 200)
         (= (timeTerre city1 city4) 200)
         (= (timeTerre city1 city2) 700)
         (= (timeTerre city1 city3) 900)
         
; city2
         (= (timeTerre city0 city2) 400)
         (= (timeTerre city2 city0) 400)
         (= (timeTerre city4 city2) 400)
         (= (timeTerre city2 city4) 400)
         (= (timeTerre city2 city1) 700)
         (= (timeTerre city2 city3) 1100)
         
; city3
         (= (timeTerre city0 city3) 600)
         (= (timeTerre city3 city0) 600)
         (= (timeTerre city4 city3) 600)
         (= (timeTerre city3 city4) 600)
         (= (timeTerre city3 city1) 900)
         (= (timeTerre city3 city2) 1100)
         
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
; 2400 400
; 2000 600
; 1600 800
; 1200 1000
; 800 1200
