package com.example.algorithm

import kotlin.random.Random;

val N = 10

fun getRandomList(random : Random) : MutableList<Int>
	= MutableList(N){random.nextInt(0,100)}

fun insertionSort(l : MutableList<Int>){
	for (i in 0..l.size-1){
		var j : Int = i-1
		while( j >= 0 && l[j] > l[j+1]){
			val tmp : Int = l[j]  
			l[j] = l[j+1]
			l[j+1] = tmp
			j--
		}
	}
}

fun bubbleSort(l : MutableList<Int>) {
	for (i in 0..l.size-1){
		for (j in 0..l.size-i-2){
			if(l[j] > l[j+1]){
				val tmp = l[j]
				l[j] = l[j+1]
				l[j+1] = tmp
			}
		}
	}
}

fun selectionSort(l : MutableList<Int>) {

	for (i in l.size-1 downTo 0){
		var max : Int = i 
		
		for(j in 0..i-1){
			if(l[max] < l[j]){
				max = j
			}
		}

		val tmp = l[i]
		l[i] = l[max]
		l[max] = tmp
	}

}

fun heapSort(l : MutableList<Int>) {
}

fun mergeSort(l : MutableList<Int>) {
}

fun inplaceMergeSort(l : MutableList<Int>) {
}

fun quickSort(l : MutableList<Int>) {
}


fun main(){

	val functions = listOf(::insertionSort, ::bubbleSort, ::selectionSort, 
		::heapSort, ::mergeSort, ::inplaceMergeSort, ::quickSort)

	for ( func in functions ){
		var l = getRandomList(Random(43))
		func(l)
		println(l)
	}
}