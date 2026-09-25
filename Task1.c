#include <stdio.h>

int main() {
    int N, i;
    char season, room;
    int nights;
    float rate, total, discount;
    float hotelTotal = 0;

    printf("Enter number of guests: ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {

        printf("\nGuest %d\n", i);

        printf("Enter season (P for Peak, O for Off-Peak): ");
        scanf(" %c", &season);

        printf("Enter room type (S for Standard, D for Deluxe, U for Suite): ");
        scanf(" %c", &room);

        printf("Enter number of nights: ");
        scanf("%d", &nights);

        // Nested pricing logic
        if (season == 'P' || season == 'p') {

            if (room == 'S' || room == 's')
                rate = 5000;
            else if (room == 'D' || room == 'd')
                rate = 8000;
            else if (room == 'U' || room == 'u')
                rate = 12000;

        }
        else if (season == 'O' || season == 'o') {

            if (room == 'S' || room == 's')
                rate = 3000;
            else if (room == 'D' || room == 'd')
                rate = 5000;
            else if (room == 'U' || room == 'u')
                rate = 8000;
        }

        // Calculate total before discount
        total = rate * nights;

        // Long-stay discount
        if (nights > 7) {
            discount = total * 0.15;
            total = total - discount;
        }

        printf("Final Price for Guest %d = Rs. %.2f\n", i, total);

        // Add guest total to hotel revenue
        hotelTotal = hotelTotal + total;
    }

    printf("\nHotel Total Revenue = Rs. %.2f\n", hotelTotal);

    return 0;
}