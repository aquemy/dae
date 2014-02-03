(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 - person
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
; 33.5778 16
; 32.7669 18
; 31.9559 20
; 31.145 22
; 30.3341 24
; 29.5231 26
; 28.7122 28
; 27.9013 30
; 27.0904 32
; 26.515 34
; 25.7041 36
; 25.1287 38
; 24.3178 40
; 23.7424 42
; 22.9315 44
; 22.3561 46
; 21.5452 48
; 20.9698 50
; 20.1589 52
; 19.5835 54
; 18.7726 56
; 18.1972 58
; 17.3863 60
; 16 64
