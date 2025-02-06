#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double calculateImportedBill(double imported_units,double* countedUnits)
{
    double st_total = 0, non_st_total = 0, KWTHBB = 0, grant_total = 0, total = 0, tax = 0;
    // Tariff calculation for the first 200 kWh
    //Phase 1
    cout << "imported_units: " << imported_units << endl;
    if (imported_units > 200)
    {
        non_st_total += 200 * 0.218;
        countedUnits[0]=200 ;
        imported_units -= 200;
        cout << "non_st_total: " << non_st_total << endl;
    }
    else
    {
        non_st_total += imported_units * 0.218;
        countedUnits[0]=imported_units;
        imported_units = 0;
                cout << "non_st_total: " << non_st_total << endl;

    }
    // Tariff calculation for the next 100 kWh (201-300)
    //Phase 2
    if (imported_units > 100)
    {
        non_st_total += 100 * 0.334;
        countedUnits[1]=100;
        imported_units -= 100;
                cout << "non_st_total: " << non_st_total << endl;

    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units* 0.334;
        countedUnits[1]=imported_units;
        imported_units = 0;
                cout << "non_st_total: " << non_st_total << endl;

    }

    // Tariff calculation for the next 300 kWh (301-600)
    //Phase 3
    if (imported_units > 300)
    {
        non_st_total += 300 * 0.516;
        countedUnits[2]=300;
        imported_units -= 300;
                cout << "non_st_total: " << non_st_total << endl;

    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units * 0.516;
        countedUnits[2]=imported_units;
        imported_units = 0;
                cout << "non_st_total: " << non_st_total << endl;

    }

    // Tariff calculation for the next 300 kWh (601-900)
    //Phase 4
    if (imported_units > 300)
    {
        st_total += 300 * 0.546;
        countedUnits[3]=300;
        imported_units -= 300;
                cout << "st_total: " << non_st_total << endl;

    }
    else if (imported_units > 0)
    {
        st_total += imported_units * 0.546;
        countedUnits[3]=imported_units;
        imported_units = 0;
                cout << "st_total: " << non_st_total << endl;

    }

    // Tariff calculation for units over 900 kWh
    //Phase 5
    if (imported_units > 0)
    {
        st_total += imported_units * 0.571;
        countedUnits[4]=imported_units;
                cout << "st_total: " << non_st_total << endl;

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



void calculateExportedBill(double imported_units, double solar_units, double total, double* countedUnits)
{
    double export_total = 0;
    double export_units = 0;
    double export_counted_units[5] = {};
    double temp = 0;
    int stopIndex = 0;
    for (int i = 0; i < 5; i++) {
        cout << "before countedUnits[" << i << "]: " << countedUnits[i] << endl;
        if (countedUnits[i] == 0) {
            stopIndex = i-1;
        }
    }
    if (imported_units == solar_units)
    {
        export_total = 0;
    }
    else if (imported_units > solar_units)
    {
        for (int i = stopIndex; i >- 1; i--)
        {
            if (solar_units != 0)
            {
               
               temp= abs(countedUnits[i]-solar_units);
               solar_units-=countedUnits[i];
               countedUnits[i]=temp;
               cout << "temp: " << temp << endl;
               if (solar_units == abs(temp))
               {
                   countedUnits[i]=0;
               }               
               cout << "solar_units: " << solar_units << endl;
               if(solar_units < 0)
                {
                    break;
                }           
                export_total+=countedUnits[i];

            }        
        } 
        for (int i = 0; i < 5; i++) {
            export_units+=countedUnits[i];
        }  
        export_total= calculateImportedBill(export_units,export_counted_units);
        cout << "Your estimated electricity bill is: RM " << export_total << endl;

    }
    else
    {
        export_total = solar_units- imported_units;
        cout << "A total of " << export_total << " kWh will be credited toward your next month's electricity bill." << endl;    
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
    string comment;
    cout << "Rate the system (1-5): ";
    cin >> rating;
    cout << "Leave a comment to us!: ";
    cin >> comment;

    if (rating >= 1 && rating <= 5)
    {
        cout << "Thank you for rating us " << rating << " stars!" << endl;
        cout << "Thank you for leaving a comment to us " << comment  << endl;

    }
    else
    {
        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
    }
}

void smartLivingGuide(){
    //dummy smart living guide
    cout << "Smart Living Guide\n";
    cout << "1. Use energy-efficient appliances\n";
    cout << "2. Turn off lights when not in use\n";
    cout << "3. Unplug devices when not in use\n";
    cout << "4. Use natural light during the day\n";
    cout << "5. Use solar panels to generate electricity\n";
    cout << "6. Use energy-efficient light bulbs\n";
    cout << "7. Use a programmable thermostat\n";
    cout << "8. Use a smart power strip\n";
    cout << "9. Use a ceiling fan\n";
    cout << "10. Use a laptop instead of a desktop computer\n";
}

int main()
{
    string name;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "\nHello, " << name << "! Welcome to the Energy Management System.\n";
    double countedUnits[5] = {};

    int selected_num;
    do
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Electricity Bill Calculation\n";
        cout << "2. Carbon Footprint with Solar\n";
        cout << "3. Rate the System\n";
        cout << "4. Smart Living Guide\n";
        cout << "5. Exit\n";
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
            double bill = calculateImportedBill(units,countedUnits);
            calculateExportedBill(units, solar_units, bill,countedUnits);
            break;
        }
        case 2:
            carbonFootprintWithSolar();
            break;
        case 3:
            rateTheSystem();
            break;
        case 4:
             smartLivingGuide();
            break;
        case 5:
            cout << "Exiting... Thank you for using the system, " << name << "!\n";
            break;
        default:
            cout << "Invalid option! Please select a valid option.\n";
        }

    } while (selected_num != 4);

    return 0;
}
