// on-the-spot activity
// Oct 8 2024 (Tue) (PAASCU accreditation)
// sorting of arrays via basic bubble sort
// similar to DSA basics

// Sample program execution
// Input #'s: 5 7 2 1 6
//
// Input Array: 5 7 2 1 6 
//
//   === Exchange Sort ===
// Pass 1:	Iter 1: 5 7 2 1 6 
// 	 		Iter 2: 5 2 7 1 6 
// 			Iter 3: 5 2 1 7 6 
// 	 		Iter 4: 5 2 1 6 7 
//
// Pass 2:	Iter 1: 2 5 1 6 7 
//			Iter 2: 2 1 5 6 7 
//			Iter 3: 2 1 5 6 7 
//			Iter 4: 2 1 5 6 7 
//
// Pass 3:	Iter 1: 1 2 5 6 7 
//			Iter 2: 1 2 5 6 7 
//			Iter 3: 1 2 5 6 7 
//			Iter 4: 1 2 5 6 7 
//
// Pass 4:	Iter 1: 1 2 5 6 7 
//			Iter 2: 1 2 5 6 7 
//			Iter 3: 1 2 5 6 7 
//			Iter 4: 1 2 5 6 7 
//
// Sorted array via Exchange sort: 1 2 5 6 7 

package LE05;

import java.util.Scanner;
import java.util.Arrays;

public class ArraySorts {

	public static void main(String[] args) {
		// declarations
		Scanner sc = new Scanner(System.in);
		int size;
		String[] inputs;
		Integer[] numbers, sorted, exSort;
		
		// user prompt and input
		System.out.print("Input #'s: ");
		inputs = sc.nextLine().strip().split(" ");
		System.out.println();
		
		// conversion of String[] to Integer[]
		size = inputs.length;
		numbers = new Integer[size];
		for(int i = 0; i < size; i++) { numbers[i] = Integer.parseInt(inputs[i]); }
		
		// pre-sorted array (solution array)
		sorted = numbers.clone();
		Arrays.sort(sorted);
		
		// unsorted array sanity check
		System.out.print("Input Array: ");
		printArray(numbers);
//		System.out.print("Method call Arrays.equals(sorted, numbers): ");
//		System.out.println(Arrays.equals(sorted, numbers));
		System.out.println();
		
		// Exchange / Bubble Sort
		System.out.println("  === Exchange Sort ===");
		exSort = numbers.clone();
		
		for (int i = 0; i < size - 1; i++) { // Pass loop
			System.out.print("Pass " + (i + 1) + ":\t");
			for (int j = 0; j < size - 1; j++) { // Iter loop
				System.out.print((j == 0 ? "" : "\t") + "Iter " + (j + 1) + ": ");
				if (exSort[j] > exSort[j + 1]) { // Swapping step (ascending)
					int x = exSort[j];
					exSort[j] = exSort[j + 1];
					exSort[j + 1] = x;
				}
				printArray(exSort);
			}
			System.out.println();
		}
		
		// Sorted array printout
//		System.out.print("Method call Arrays.equals(sorted, exSort): ");
//		System.out.println(Arrays.equals(sorted, exSort));
		System.out.print("Sorted array via Exchange sort: ");
		printArray(exSort);
		
		// closing the Scanner object
		sc.close();
	}
	
	// prints a provided array
	public static void printArray(Integer[] arr) {
		for(int i : arr) {
			System.out.print(i + " ");
		}
		System.out.println();
	}
}
