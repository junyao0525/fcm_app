#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void UpdateText()
{
    cout << "=================================="
         << endl;
    cout << "Upgrade to Energy-Efficient Appliances"
         << endl;
    cout << "=================================="
         << endl;

    cout
        << "1.Smart Thermostats"
        << endl;
    cout << "Install a smart thermostat that learns your schedule and adjusts heating and cooling automatically.\n"
         << endl;

    cout << "2.Energy-Efficient Lighting"
         << endl;
    cout << "Replace traditional bulbs with LED smart bulbs that can be controlled remotely.\n"
         << endl;

    cout << "3.High-Efficiency Appliances"
         << endl;
    cout << "When replacing old appliances, opt for Energy Star-rated products.\n"
         << endl;
}

void OptimizeText()
{
    cout << "=================================="
         << endl;
    cout << "Optimize Your Home with Smart Technology"
         << endl;
    cout << "=================================="
         << endl;

    cout
        << "1.Smart Plugs and Power Strips"
        << endl;
    cout << "Monitor and control power usage of individual devices with automated schedules.\n"
         << endl;

    cout << "2.Home Energy Monitors"
         << endl;
    cout << "Track real-time energy consumption data to identify areas for imporvement.\n"
         << endl;

    cout << "3.Automated Window Treatments"
         << endl;
    cout << "Install smart blinds that adjust based on sunlight and time of day.\n"
         << endl;
}

void CommunityText()
{
    cout << "=================================="
         << endl;
    cout << "Engage with Community and Stay Informed"
         << endl;
    cout << "=================================="
         << endl;

    cout
        << "1.Join Green Initiatives"
        << endl;
    cout << "Participate in  local sustainability communities and share experiences.\n"
         << endl;

    cout << "2.Stay Updated on Technology"
         << endl;
    cout << "Follow blogs, podcasts, and webinars about smart home technology advancements.\n"
         << endl;

    cout << "3.Monitor Your Progress"
         << endl;
    cout << "Use apps and dashboards to track yout energy usage and savings over time.\n"
         << endl;
}

double calculateImportedBill(double imported_units, double *countedUnits)
{
    double st_total = 0, non_st_total = 0, KWTHBB = 0, grant_total = 0, total = 0, tax = 0;
    // Tariff calculation for the first 200 kWh
    // Phase 1
    cout << "imported_units: " << imported_units << endl;
    if (imported_units > 200)
    {
        non_st_total += 200 * 0.218;
        countedUnits[0] = 200;
        imported_units -= 200;
        cout << "non_st_total: " << non_st_total << endl;
    }
    else
    {
        non_st_total += imported_units * 0.218;
        countedUnits[0] = imported_units;
        imported_units = 0;
        cout << "non_st_total: " << non_st_total << endl;
    }
    // Tariff calculation for the next 100 kWh (201-300)
    // Phase 2
    if (imported_units > 100)
    {
        non_st_total += 100 * 0.334;
        countedUnits[1] = 100;
        imported_units -= 100;
        cout << "non_st_total: " << non_st_total << endl;
    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units * 0.334;
        countedUnits[1] = imported_units;
        imported_units = 0;
        cout << "non_st_total: " << non_st_total << endl;
    }

    // Tariff calculation for the next 300 kWh (301-600)
    // Phase 3
    if (imported_units > 300)
    {
        non_st_total += 300 * 0.516;
        countedUnits[2] = 300;
        imported_units -= 300;
        cout << "non_st_total: " << non_st_total << endl;
    }
    else if (imported_units > 0)
    {
        non_st_total += imported_units * 0.516;
        countedUnits[2] = imported_units;
        imported_units = 0;
        cout << "non_st_total: " << non_st_total << endl;
    }

    // Tariff calculation for the next 300 kWh (601-900)
    // Phase 4
    if (imported_units > 300)
    {
        st_total += 300 * 0.546;
        countedUnits[3] = 300;
        imported_units -= 300;
        cout << "st_total: " << non_st_total << endl;
    }
    else if (imported_units > 0)
    {
        st_total += imported_units * 0.546;
        countedUnits[3] = imported_units;
        imported_units = 0;
        cout << "st_total: " << non_st_total << endl;
    }

    // Tariff calculation for units over 900 kWh
    // Phase 5
    if (imported_units > 0)
    {
        st_total += imported_units * 0.571;
        countedUnits[4] = imported_units;
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

void calculateExportedBill(double imported_units, double solar_units, double total, double *countedUnits)
{
    double export_total = 0;
    double export_units = 0;
    double export_counted_units[5] = {};
    double temp = 0;
    int stopIndex = 0;
    for (int i = 0; i < 5; i++)
    {
        cout << "before countedUnits[" << i << "]: " << countedUnits[i] << endl;
        if (countedUnits[i] == 0)
        {
            stopIndex = i - 1;
        }
    }
    if (imported_units == solar_units)
    {
        export_total = 0;
    }
    else if (imported_units > solar_units)
    {
        for (int i = stopIndex; i > -1; i--)
        {
            if (solar_units != 0)
            {

                temp = abs(countedUnits[i] - solar_units);
                solar_units -= countedUnits[i];
                countedUnits[i] = temp;
                cout << "temp: " << temp << endl;
                if (solar_units == abs(temp))
                {
                    countedUnits[i] = 0;
                }
                cout << "solar_units: " << solar_units << endl;
                if (solar_units < 0)
                {
                    break;
                }
                export_total += countedUnits[i];
            }
        }
        for (int i = 0; i < 5; i++)
        {
            export_units += countedUnits[i];
        }
        export_total = calculateImportedBill(export_units, export_counted_units);
        cout << "Your estimated electricity bill is: RM " << export_total << endl;
    }
    else
    {
        export_total = solar_units - imported_units;
        cout << "A total of " << export_total << " kWh will be credited toward your next month's electricity bill." << endl;
    }
}

void carbonFootprintWithSolar()
{
    const double CO2_PER_KWH = 0.4;    // kg CO2 per kWh
    const double SOLAR_SAVINGS = 0.85; // kWh savings potential
    const double TREE_CO2_ABSORPTION = 21.0;
    double energy_consumed, solar_offset;
    cout << "Enter your monthly electricity consumption (kWh): ";
    cin >> energy_consumed;

    if (energy_consumed <= 0)
    {
        cout << "Please enter a valid electricity consumption.\n";
        return;
    }

    double carbonFootprint = energy_consumed * CO2_PER_KWH;
    double potentialSolarSavings = energy_consumed * SOLAR_SAVINGS;
    int treesNeeded = ceil(carbonFootprint / TREE_CO2_ABSORPTION);

    cout << "Monthly Electricity Consumption: "
         << fixed << setprecision(1) << energy_consumed << " kWh\n";
    cout << "Carbon Footprint: "
         << fixed << setprecision(1) << carbonFootprint << " kg CO2\n";
    cout << "Potential Solar Savings: "
         << fixed << setprecision(1) << potentialSolarSavings << " kWh\n";
    cout << "Trees Needed to Offset: " << treesNeeded << " trees/year\n";
}

void smartLivingGuide()
{
    int selected_num;
    do
    {
        cout
            << "\n==================================" << endl;
        cout << "      Smart Living Guide" << endl;
        cout << "==================================" << endl;
        cout << "A guide for greener lifestyle with smart home technology\n"
             << endl;

        cout << "Main Categories:\n";

        cout << "1. Upgrade to Energy-Efficient Appliances\n";
        cout << "2. Optimize Your Home with Smart Technology\n";
        cout << "3. Engage with Community and Stay Informed\n";
        cout << "0. Exit Program\n";
        cout << "Select an option (0-3): ";

        cin >> selected_num;

        switch (selected_num)
        {
        case 1:
            UpdateText();
            break;
        case 2:
            OptimizeText();
            break;
        case 3:
            CommunityText();
            break;
        case 0:
            cout << "Exiting... Thank you for using the Smart Living Guide system !\n";
            break;
        default:
            cout << "Invalid option! Please select a valid option.\n";
        }
    } while (selected_num != 0);
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
        cout << "3. Smart Living Guide\n";
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
            double bill = calculateImportedBill(units, countedUnits);
            calculateExportedBill(units, solar_units, bill, countedUnits);
            break;
        }
        case 2:
            carbonFootprintWithSolar();
            break;
        case 3:
            smartLivingGuide();
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
