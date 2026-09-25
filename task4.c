#include <stdio.h>

// Function 1: Calculate Subtotal
float calculateSubtotal(int q, float p) {
    return q * p;
}

// Function 2: Apply Discount
float calculateDiscountedAmount(float s, float d) {
    return s - (s * d) / 100;
}

// Function 3: Calculate Final Bill
float calculateFinalBill(float a, float t) {
    return a + (a * t) / 100;
}

int main() {

    int quantity;
    float price, discount, tax;
    float subtotal, discountedAmount, finalBill;

    // Input
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    printf("Enter price per item: ");
    scanf("%f", &price);

    printf("Enter discount percentage: ");
    scanf("%f", &discount);

    printf("Enter tax percentage: ");
    scanf("%f", &tax);

    // Validation
    if (quantity <= 0) {
        printf("Error: Quantity must be greater than 0.\n");
        return 0;
    }

    if (price < 0) {
        printf("Error: Price cannot be negative.\n");
        return 0;
    }

    if (discount < 0 || discount > 100) {
        printf("Error: Discount must be between 0 and 100.\n");
        return 0;
    }

    if (tax < 0) {
        printf("Error: Tax cannot be negative.\n");
        return 0;
    }

    // Calculations
    subtotal = calculateSubtotal(quantity, price);

    discountedAmount = calculateDiscountedAmount(subtotal, discount);

    finalBill = calculateFinalBill(discountedAmount, tax);

    // Bill
    printf("\n========== SHOPPING BILL ==========\n");
    printf("Quantity          : %d\n", quantity);
    printf("Price per Item    : Rs. %.2f\n", price);
    printf("Subtotal          : Rs. %.2f\n", subtotal);
    printf("Discount          : %.2f%%\n", discount);
    printf("Discounted Amount : Rs. %.2f\n", discountedAmount);
    printf("Tax               : %.2f%%\n", tax);
    printf("Final Bill        : Rs. %.2f\n", finalBill);
    printf("===================================\n");

    return 0;
}