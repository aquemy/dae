(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 - person
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
; 9600 1600
; 9200 1800
; 8800 2000
; 8400 2200
; 8000 2400
; 7600 2600
; 7200 2800
; 6800 3000
; 6400 3200
; 6000 3400
; 5600 3600
; 5200 3800
; 4800 4000
; 4400 4200
; 4000 4400
; 3600 4600
; 3200 4800
