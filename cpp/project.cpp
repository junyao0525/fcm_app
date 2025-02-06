#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double calculateImportedBill(double imported_units)
{
    double st_total = 0, non_st_total = 0, KWTHBB = 0, grant_total = 0, total = 0, tax = 0;

    // Tariff calculation for the first 200 kWh
    if (imported_units > 200)
    {
        non_st_total += 200 * 0.218;
        imported_units -= 200;
    }
    else
    {
        non_st_total += imported_units * 0.218;
        imported_units = 0;
    }

    // Tariff calculation for the next 100 kWh (201-300)
    if (imported_units > 100)
    {
        non_st_total += 100 * 0.334;
        imported_units -= 100;
    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units * 0.334;
        imported_units = 0;
    }

    // Tariff calculation for the next 300 kWh (301-600)
    if (imported_units > 300)
    {
        non_st_total += 300 * 0.516;
        imported_units -= 300;
    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units * 0.516;
        imported_units = 0;
    }

    // Tariff calculation for the next 300 kWh (601-900)
    if (imported_units > 300)
    {
        st_total += 300 * 0.546;
        imported_units -= 300;
    }
    else if (imported_units > 0)
    {
        st_total += imported_units * 0.546;
        imported_units = 0;
    }

    // Tariff calculation for units over 900 kWh
    if (imported_units > 0)
    {
        st_total += imported_units * 0.571;
    }

    // Add service tax (6%) and KWTHBB charge (1.6%)
    non_st_total = round(non_st_total * 100) / 100;
    st_total = round(st_total * 100) / 100;

    // cout << "non_st_total: " << non_st_total << endl;
    // cout << "st_total: " << st_total << endl;

    grant_total = (non_st_total + st_total);
    // cout << "Grant Total: " << grant_total << endl;

    tax = (st_total * 0.08);
    KWTHBB = (grant_total * 0.016);

    tax = round(total * 100) / 100;
    KWTHBB = round(total * 100) / 100;

    // cout << "tax: " << tax << endl;
    // cout << "KWTHBB: " << KWTHBB << endl;

    total = non_st_total + st_total + tax + KWTHBB;
    total = round(total * 100) / 100;

    return total;
}

void calculateExportedBill(double imported_units, double solar_units, double total)
{
    double export_total = 0;
    double export_units = 0;
    // 400
    if (imported_units == solar_units)
    {
        export_total = 0;
    }
    else if (imported_units > solar_units)
    {
        export_total = (imported_units - solar_units) * 0.218;
        if (imported_units > 200)
        {
            non_st_total += 200 * 0.218;
            imported_units -= 200;
        }
        else
        {
            non_st_total += imported_units * 0.218;
            imported_units = 0;
        }
    }
    else
    {
    }
}

void carbonFootprintWithSolar()
{
    double energy_consumed, solar_offset;
    cout << "Enter your monthly electricity consumption (kWh): ";
    cin >> energy_consumed;
    cout << "Enter the percentage of energy offset by solar (0-100): ";
    cin >> solar_offset;

    double footprint_without_solar = energy_consumed * 0.92; // 0.92 kg CO2 per kWh
    double footprint_with_solar = footprint_without_solar * ((100 - solar_offset) / 100);

    cout << "Your estimated carbon footprint without solar: " << footprint_without_solar << " kg CO2" << endl;
    cout << "Your estimated carbon footprint with solar: " << footprint_with_solar << " kg CO2" << endl;
}

void rateTheSystem()
{
    int rating;
    cout << "Rate the system (1-5): ";
    cin >> rating;

    if (rating >= 1 && rating <= 5)
    {
        cout << "Thank you for rating us " << rating << " stars!" << endl;
    }
    else
    {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
    }
}

int main()
{
    string name;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "\nHello, " << name << "! Welcome to the Energy Management System.\n";

    int selected_num;
    do
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Electricity Bill Calculation\n";
        cout << "2. Carbon Footprint with Solar\n";
        cout << "3. Rate the System\n";
        cout << "4. Exit\n";
        cout << "Select an option (1-4): ";
        cin >> selected_num;

        switch (selected_num)
        {
        case 1:
        {
            double units, solar_units;
            cout << "Total Consumption (kWh):";
            cin >> units;
            cout << "Export Green Electricity (kWh):";
            cin >> solar_units;
            double bill = calculateImportedBill(units);
            cout << "Your estimated electricity bill is: RM " << bill << endl;
            break;
        }
        case 2:
            carbonFootprintWithSolar();
            break;
        case 3:
            rateTheSystem();
            break;
        case 4:
            cout << "Exiting... Thank you for using the system, " << name << "!\n";
            break;
        default:
            cout << "Invalid option! Please select a valid option.\n";
        }

    } while (selected_num != 4);

    return 0;
}
