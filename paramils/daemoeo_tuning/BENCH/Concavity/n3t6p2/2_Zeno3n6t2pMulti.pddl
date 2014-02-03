(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 50)
         (= (citythreat city2) 91.4214)
         (= (citythreat city3) 123.205)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 123.205)
         (= (timeTerre city1 city0) 123.205)
         (= (timeTerre city4 city1) 123.205)
         (= (timeTerre city1 city4) 123.205)
         
; city2
         (= (timeTerre city0 city2) 91.4214)
         (= (timeTerre city2 city0) 91.4214)
         (= (timeTerre city4 city2) 91.4214)
         (= (timeTerre city2 city4) 91.4214)
         
; city3
         (= (timeTerre city0 city3) 50)
         (= (timeTerre city3 city0) 50)
         (= (timeTerre city4 city3) 50)
         (= (timeTerre city3 city4) 50)
         
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
; 1232.05 500
; 1168.48 582.843
; 1085.64 646.41
; 1022.07 729.253
; 939.23 792.82
; 875.663 875.663
; 792.82 939.23
; 729.253 1022.07
; 646.41 1085.64
; 582.843 1168.48
; 500 1232.05
