#include "src/education/EducationModule.h"
#include "src/public/PublicModule.h"
#include "src/population/populationModule.h"
#include "src/commercial/CommercialModule.h"
#include "src/transport/TransportModule.h"
#include "src/medical/PharmacyModule.h"
#include "src/medical/HospitalModule.h"

#include "conio.h"
#include <limits>

      
class CityManager
{
    Sector::Graph sectorGraph;
    EducationModule educationModule;
    PublicModule publicModule;
    Population::populationModule popModule;
    CommercialModule commercialModule;
    TransportModule transportModule;
    PharmacyModule pharmacyModule;
    HospitalModule hospitalModule;

    void printMainMenu()
    {
        cout << "================= City Management System =================" << endl;
        
        cout << "Main Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Education Module" << endl;
        cout << "2. Public Facilities Module" << endl;
        cout << "3. Map Module" << endl;
        cout << "4. Population Module" << endl;
        cout << "5. Commercial Module" << endl;
        cout << "6. Transport Module" << endl;
        cout << "7. Pharmacy Module" << endl;
        cout << "8. Hospital Module" << endl;
        cout << "9. Exit" << endl;
    }

     void printPublicFacilitiesMenu()
    {
        cout << "================= Public Facilities Module =================" << endl;
        
        cout << "Public Facilities Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. View All Public Facilities" << endl;
        cout << "2. View Public Facilities by Type" << endl;
        cout << "3. Search for a Public Facility" << endl;
        cout << "4. Find Nearest Public Facility" << endl;
        cout << "5. Add Public Facility" << endl;
        cout << "6. Back to Main Menu" << endl;
    }

    void printMapMenu()
    {
        cout << "================= Map Module =================" << endl;
        
        cout << "Map Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Print Sector Network" << endl;
        cout << "2. Search Sector" << endl;
        cout << "3. Print Facilities in Sector" << endl;
        cout << "4. Add Sector" << endl;
        cout << "5. Get Shortest Path Between 2 Sectors" << endl;
        cout << "6. Node Count and Edge Count" << endl;
        cout << "7. Degree of a Sector" << endl;
        cout << "8. Back to Main Menu" << endl;
    }

    void pritnSchoolsMenu()
    {
        cout << "================= Schools Module =================" << endl;
        
        cout << "Schools Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Print All Schools" << endl;
        cout << "2. Search for a School" << endl;
        cout << "3. Search By Subject" << endl;
        cout << "4. Find Nearest School" << endl;
        cout << "5. Register Faculty Member" << endl;
        cout << "6. Register Student" << endl;
        cout << "7. Add School" << endl;
        cout << "8. Print Organogram" << endl;
        cout << "9. Back to Main Menu" << endl;
    }

    void printCommercialMenu()
    {
        cout << "================= Commercial Module =================" << endl;
        cout << "Commercial Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Register Mall" << endl;
        cout << "2. Add Product to Mall" << endl;
        cout << "3. Display All Malls" << endl;
        cout << "4. Search Product by Name" << endl;
        cout << "5. Search Product by Category" << endl;
        cout << "6. Display Mall Details" << endl;
        cout << "7. Find Nearest Mall" << endl;
        cout << "8. Back to Main Menu" << endl;
    }

    void printPopulationMenu()
    {
        cout << "================= Population Module =================" << endl;
        cout << "Population Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Add Person" << endl;
        cout << "2. Find Person" << endl;
        cout << "3. Print Family Tree" << endl;
        cout << "4. Assign Relations" << endl;
        cout << "5. Total Residents in a House" << endl;
        cout << "6. Total Population in a street" << endl;
        cout << "7. Total Population in a sector" << endl;
        cout << "8. Total Population in the City" << endl;
        cout << "9. Back to Main Menu" << endl;
    }


    void printTransportMenu()
    {
        cout << "================= Transport Module =================" << endl;
        cout << "Transport Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Print Companies" << endl;
        cout << "2. Display Bus Details" << endl;
        cout << "3. Search Stop by ID" << endl;
        cout << "4. Nearest Bus to Stop" << endl;
        cout << "5. Shortest Path Between Stops" << endl;
        cout << "6. Emergency Route for Bus" << endl;
        cout << "7. Bus Simulation" << endl;
        cout << "8. Register New Bus Company" << endl;
        cout << "9. School Buses" << endl;
        cout << "A. Track Bus Route" << endl;
        cout << "B. Back to Main Menu" << endl;
    }

    void printPharmacyMenu()
    {
        cout << "================= Pharmacy Module =================" << endl;
        cout << "Pharmacy Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Display All Pharmacies" << endl;
        cout << "2. Search Medicine by Name" << endl;
        cout << "3. Search Medicine by Formula" << endl;
        cout << "4. Display Pharmacy Details" << endl;
        cout << "5. Add New Pharmacy" << endl;
        cout << "6. Find Pharmacy by Name" << endl;
        cout << "7. Find Nearest Pharmacy" << endl;
        cout << "8. Add Medicine to Pharmacy" << endl;
        cout << "9. Back to Main Menu" << endl;
    }


    void printHospitalModule()
    {
        cout << "================== Hospital Module =================" << endl;
        cout << "Hospital Menu:" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Display All Hospitals" << endl;
        cout << "2. Display Emergency Bed Availability" << endl;
        cout << "3. Register Dcotor" << endl;
        cout << "4. Add Patient" << endl;
        cout << "5. Display Hospital Details" << endl;
        cout << "6. Find Nearest Hospital" << endl;
        cout << "7. Update Bed Availability" << endl;
        cout << "8. Search by Specialization" << endl;
        cout << "9. Total Beds in City" << endl;
        cout << "A. Average Beds per Hospital" << endl;
        cout << "B. Back to Main Menu" << endl;
    }

    void mapModule()
    {
        char input = 1;

        do
        {
            printMapMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch(input)
            {
                case '1':
                    {
                        // Print Sector Network
                        cout << "Sector Network:" << endl;
                        sectorGraph.print();
                        break;
                    }
                case '2':
                    {
                        // Search Sector
                        string name;
                        cout << "Enter Sector Name to Search: ";
                        getline(cin, name);
                        if(sectorGraph.searchSector(name))
                            cout << "Sector '" << name << "' found." << endl;
                        else
                            cout << "Sector '" << name << "' not found." << endl;
                        break;
                    }
                
                case '3':
                {
                    // Print Facilities in Sector
                    string sectorName;
                    cout << "Enter Sector Name to View Facilities: ";
                    getline(cin, sectorName);
                    if(!sectorGraph.searchSector(sectorName))
                    {
                        cout << "Sector '" << sectorName << "' not found." << endl;
                        break;
                    }
                    sectorGraph.printFacilities(sectorName);
                    break;
                }

                case '4':
                {
                    // Add Sector
                    string name;
                    cout << "Enter New Sector Name to Add: ";
                    getline(cin, name);

                   

                    if(sectorGraph.searchSector(name))
                    {
                        cout << "Sector '" << name << "' already exists." << endl;
                        break;
                    }
                    sectorGraph.addSector(name);
                    popModule.addSector(name); // add as a valid sector in population module too
                    cout << "Sector '" << name << "' added successfully." << endl;

                    cout << "How many neighbours to add? (0 for no neighbours)" << endl;
                    cout << "Enter Number of Neighbours: ";
                    int neighbourCount;
                    cin >> neighbourCount;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    for(int i = 0; i < neighbourCount; i++)
                    {
                        string neighbourName;
                        int weight;
                        cout << "Enter Neighbour " << (i+1) << " Name: ";
                        getline(cin, neighbourName);
                        if(!sectorGraph.searchSector(neighbourName))
                        {
                            cout << "Sector '" << neighbourName << "' does not exist. Please add it first." << endl;
                            i--;
                            continue;
                        }
                        cout << "Note: Weight Between adjacent sectors is 1 so use that for reference" << endl;
                        cout << "Enter Weight to Neighbour " << (i+1) << ": ";
                        cin >> weight;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if(weight <= 0)
                        {
                            cout << "Weight must be positive." << endl;
                            i--;
                            continue;
                        }
                        sectorGraph.addNeighbour(name, neighbourName, weight);
                    }
                    break;
                }
                case '5':
                    {
                        // Get Shortest Path Between 2 Sectors
                        string startSector, endSector;
                        cout << "Enter Start Sector Name: ";
                        getline(cin, startSector);
                        if(!sectorGraph.searchSector(startSector))
                        {
                            cout << "Sector '" << startSector << "' not found." << endl;
                            break;
                        }
                        cout << "Enter End Sector Name: ";
                        getline(cin, endSector);
                        if(!sectorGraph.searchSector(endSector))
                        {
                            cout << "Sector '" << endSector << "' not found." << endl;
                            break;
                        }

                        string* path = nullptr;
                        int pathLen = 0;
                        int dist = -1;

                        bool ok = sectorGraph.shortestPath(startSector, endSector, path, pathLen, dist);
                        if(!ok)
                        {
                            cout << "No path found between '" << startSector << "' and '" << endSector << "'." << endl;
                        }
                        else
                        {
                            cout << "Shortest Path from '" << startSector << "' to '" << endSector << "': ";
                            for(int i = 0; i < pathLen; i++)
                            {
                                cout << path[i];
                                if(i < pathLen - 1)
                                    cout << " -> ";
                            }
                            cout << " | Total Distance: " << dist << endl;
                        }

                        delete[] path;
                        break;
                    }
                case '6':
                    {
                        // Node Count and Edge Count
                        int nodeCount = sectorGraph.size();
                        int edgeCount = sectorGraph.edgeCount();
                        cout << "Sector Network has " << nodeCount << " sectors and " << edgeCount << " connections." << endl;
                        break;
                    }

                case '7':
                    {
                        // Degree of a Sector
                        string sectorName;
                        cout << "Enter Sector Name to Get Degree: ";
                        getline(cin, sectorName);
                        if(!sectorGraph.searchSector(sectorName))
                        {
                            cout << "Sector '" << sectorName << "' not found." << endl;
                            break;
                        }
                        int degree = sectorGraph.degree(sectorName);
                        if(degree == -1)
                        {
                            cout << "Sector '" << sectorName << "' not found." << endl;
                        }
                        else
                        {
                            cout << "Sector '" << sectorName << "' has a degree of " << degree << "." << endl;
                        }
                        break;
                    }
                case '8':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");
    }while( input != '8' );
}
    void schoolsModule()
    {
        char input = 1;

        do
        {
            pritnSchoolsMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
            case '1':
                    {
                        // Print All Schools
                        cout << "All Schools:" << endl;
                        educationModule.printSchoolRanking();
                        break;
                    }
                
            case '2':
            {
                string name;
                cout << "Enter School Name to Search: ";
                getline(cin, name);
                School* s = educationModule.findSchoolByName(name);
                if(s)
                    cout << "School '" << name << "' found in Sector '" << s->getSector() << "'." << endl;
                else
                    cout << "School '" << name << "' not found." << endl;
                break;
            }

            case '3':
            {
                string subject;
                cout << "Enter Subject to Search Schools Offering It: ";
                getline(cin, subject);
                educationModule.searchBySubject(subject);

                break;
            }

            case '4':
            {
                string name;
                cout << "Enter Your Current School Name: ";
                getline(cin, name);
                School* nearest = educationModule.nearestSchoolGlobal(name);
                if(nearest)
                    cout << "Nearest School is '" << nearest->getName() << "' in Sector '" << nearest->getSector() << "'." << endl;
                else
                    cout << "No nearest School found." << endl;
                break;
            }

            case '5':
            {
                // Register Faculty Member
                string schoolName;
                cout << "Enter School Name to Register Faculty In: ";
                getline(cin, schoolName);
                School* s = educationModule.findSchoolByName(schoolName);
                if(!s)
                {
                    cout << "School '" << schoolName << "' not found." << endl;
                    break;
                }

                string id, name, subject, qualification, department, role, parentRole;
                cout << "Enter Faculty ID: ";
                getline(cin, id);
                cout << "Enter Faculty Name: ";
                getline(cin, name);
                cout << "Enter Subject: ";
                getline(cin, subject);
                cout << "Enter Qualification: ";
                getline(cin, qualification);
                cout << "Enter Department: ";
                getline(cin, department);
                cout << "Enter Role: ";
                getline(cin, role);

                cout << "Enter Parent Role in Organogram (leave blank if none): ";
                getline(cin, parentRole);
                Faculty f(id, name, subject, qualification, department, role);
                educationModule.registerFacultyWithRole(schoolName, f, parentRole);

                
                break;
            }

            case '6':
            {
                // Register Student
                string schoolName;
                cout << "Enter School Name to Register Student In: ";
                getline(cin, schoolName);
                School* s = educationModule.findSchoolByName(schoolName);
                if(!s)
                {
                    cout << "School '" << schoolName << "' not found." << endl;
                    break;
                }

                string rollNumber, name, grade, department, section;
                cout << "Enter Student ID: ";
                getline(cin, rollNumber);
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Student Grade: ";
                getline(cin, grade);
                cout << "Enter Student Department: ";
                getline(cin, department);
                cout << "Enter Student Section: ";
                getline(cin, section);

                Student st(rollNumber, name, grade, department, section);

                if(s->registerStudent(st))
                    cout << "Student '" << name << "' registered successfully in '" << schoolName << "'." << endl;
                else
                    cout << "Student with ID '" << rollNumber << "' already exists in '" << schoolName << "'." << endl;

                
                break;
            }


            case '7':
            {
                string id, name, sectorName;
                float rating;
                int subjectCount;

                cout << "Enter School ID: ";
                getline(cin, id);

                cout << "Enter New School Name: ";
                getline(cin, name);
                cout << "Enter Sector Name: ";
                getline(cin, sectorName);

                School* existing = educationModule.findSchoolByName(name);
                if(existing)
                {
                    cout << "School '" << name << "' already exists." << endl;
                    break;
                }

                if(!sectorGraph.searchSector(sectorName))
                {
                    cout << "Sector '" << sectorName << "' does not exist. Please add it first." << endl;
                    break;
                }

                cout << "Enter School Rating (0.0 - 5.0): ";
                cin >> rating;
                while(rating < 0.0 || rating > 5.0)
                {
                    cout << "Invalid rating. Please enter a value between 0.0 and 5.0: ";
                    cin >> rating;
                }

                School* s = new School(id, name, sectorName);
                s->setRating(rating);
                educationModule.addSchool(s);
                sectorGraph.addFacility(sectorName, id, name, Facility::EDUCATION);

                cout << "Enter Number of Subjects Offered: ";
                cin >> subjectCount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                for(int i = 0; i < subjectCount; i++)
                {
                    string subject;
                    cout << "Enter Subject " << (i+1) << ": ";
                    getline(cin, subject);
                    s->addSubject(subject);
                }

                cout << "School '" << name << "' added successfully." << endl;
                educationModule.buildSchoolGraph(sectorGraph); // rebuild school graph
                break;
            }

            case '8':
            {
                // Print Organogram
                string schoolName;
                cout << "Enter School Name to View Organogram: ";
                getline(cin, schoolName);
                School* s = educationModule.findSchoolByName(schoolName);
                if(!s)
                {
                    cout << "School '" << schoolName << "' not found." << endl;
                    break;
                }
                educationModule.printOrganogram(schoolName);
                break;
            }

            
                
                case '9':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '9' );
    }


    void publicFacilitiesModule()
    {
        char input = 1;

        do
        {
            printPublicFacilitiesMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
            case '1':
                    {
                        // Print all public facilities
                        publicModule.printAll();
                        break;
                    }
                case '2':
                    {
                        // Print public facilities by type
                        int typeInput;
                        cout << "Select Type to View (0: Mosque, 1: Park, 2: Water Cooler): ";
                        cin >> typeInput;
                        if (typeInput < 0 || typeInput > 2)
                        {
                            cout << "Invalid type selected." << endl;
                            break;
                        }
                        PUBLIC_TYPE type = static_cast<PUBLIC_TYPE>(typeInput);
                        publicModule.printType(type);
                        break;
                    }
                case '3':
                    {
                        // Search for a public facility
                        string name;
                        cout << "Enter Public Facility Name to Search: ";
                        getline(cin, name);
                        if(publicModule.searchFacility(name))
                            cout << "Public Facility '" << name << "' found." << endl;
                        else
                            cout << "Public Facility '" << name << "' not found." << endl;
                        break;
                    }
                case '4':
                    {
                        // Find nearest public facility
                        string name;
                        cout << "Enter Your Current Public Facility Name: ";
                        getline(cin, name);
                        PublicFacility* nearest = publicModule.nearestPublicFacility(name);
                        if(nearest)
                            cout << "Nearest Public Facility is '" << nearest->name << "' in Sector '" << nearest->sectorName << "'." << endl;
                        else
                            cout << "No nearest Public Facility found." << endl;
                        break;
                    }
                case '5':
                    {
                        // Add a new public facility
                        string name, sectorName;
                        int typeInput;
                        cout << "Enter Public Facility Name: ";
                        getline(cin, name);
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);
                        cout << "Select Type (0: Mosque, 1: Park, 2: Water Cooler): ";
                        cin >> typeInput;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        while(typeInput < 0 || typeInput > 2)
                        {
                            cout << "Invalid type. Please enter 0, 1, or 2: ";
                            cin >> typeInput;
                        }
                        PUBLIC_TYPE type = static_cast<PUBLIC_TYPE>(typeInput);
                        if (!sectorGraph.addFacility(sectorName, "", name, Facility::PUBLIC))
                        {
                            cout << "Failed to add Public Facility. Sector may not exist." << endl;
                            break;
                        }
                        publicModule.addPublicFacility(name, sectorName, type);
                        publicModule.buildSubgraph(sectorGraph); // Rebuild subgraph to include new facility
                        cout << "Public Facility '" << name << "' added successfully." << endl;
                        break;
                    }
                case '6':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '6' );


    }

    void mallModule()
    {
        char input = 1;
        do
        {
            printCommercialMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
                case '1':
                    {
                        string id, name, sectorName;
                        cout << "Enter Mall ID: ";
                        getline(cin, id);
                        cout << "Enter Mall Name: ";
                        getline(cin, name);
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);

                        if(sectorGraph.searchSector(sectorName) == false)
                        {
                            cout << "Sector '" << sectorName << "' does not exist. Please add it first." << endl;
                            break;
                        }

                        sectorGraph.addFacility(sectorName, id, name, Facility::COMMERCIAL);
                        commercialModule.registerMall(id, name, sectorName);
                        commercialModule.buildMallGraph(sectorGraph); // rebuild mall graph

                        cout << "Mall '" << name << "' registered successfully." << endl;

                        break;
                    }
                case '2':
                    {
                        string mallID, productName, category;
                        cout << "Enter Mall ID to Add Product In: ";
                        getline(cin, mallID);
                        cout << "Enter Product Name: ";
                        getline(cin, productName);
                        cout << "Enter Product Category: ";
                        getline(cin, category);

                        if(commercialModule.findMallByID(mallID) == nullptr)
                        {
                            cout << "Mall with ID '" << mallID << "' not found." << endl;
                            break;
                        }

                        commercialModule.addProductToMall(mallID, productName, category);
                        cout << "Product '" << productName << "' added to Mall ID '" << mallID << "' successfully." << endl;
                        break;
                    }
                case '3':
                    {
                        commercialModule.displayAllMalls();
                        break;
                    }
                case '4':
                    {
                        // Search Product by Name
                        Product found;
                        string mallName;
                        string productName;

                        cout << "Enter Product Name to Search: ";
                        getline(cin, productName);

                        if(commercialModule.searchProductByName(productName, mallName, found))
                        {
                            cout << "Product Found: " << found << endl;
                        }
                        else
                        {
                            cout << "Product '" << productName << "' not found in any mall." << endl;
                        }
                        
                        break;
                    }
                case '5':
                    {
                        // Search Product by Category
                        Product found;
                        string mallName;
                        string category;
                        cout << "Enter Product Category to Search: ";
                        getline(cin, category);
                        if(commercialModule.searchProductByCategory(category, mallName, found))
                        {
                            cout << "Product Found: " << found << endl;
                        }
                        else
                        {
                            cout << "No products found in category '" << category << "' in any mall." << endl;
                        }

                        break;
                    }
                case '6':
                    {
                        string mallName;
                        cout << "Enter Mall Name to Display Details: ";
                        getline(cin, mallName);
                        commercialModule.displayMallDetails(mallName);

                        break;
                    }
                case '7':
                    {
                        // Find Nearest Mall
                        string name;
                        cout << "Enter Your Current Mall Name: ";
                        getline(cin, name);
                        ShoppingMall* nearest = commercialModule.findNearestMall(name);

                        if(nearest)
                            cout << "Nearest Mall is '" << nearest->getName() << "' in Sector '" << nearest->getSector() << "'." << endl;
                        else
                            cout << "No nearest Mall found." << endl;
                        break;
                    }
                case '8':
                    {
                        // Exit Module
                      
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '8' );
    }


    void peopleModule()
    {
        char input = 1;

        do
        {
            printPopulationMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
                case '1':
                    {
                        // Add Person
                        string cnic, name, sectorName, streetName, houseNo, occupation;
                        int age;

                        cout << "Enter CNIC: ";
                        getline(cin, cnic);
                        if(!UTIL::validateCNIC(cnic))
                        {
                            cout << "Invalid CNIC format." << endl;
                            break;
                        }
                        cout << "Enter Name: ";
                        getline(cin, name);
                        cout << "Enter Age: ";
                        cin >> age;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);
                        if(!sectorGraph.searchSector(sectorName))
                        {
                            cout << "Sector '" << sectorName << "' does not exist. Please add it first." << endl;
                            break;
                        }

                        cout << "Enter Street Name: ";
                        getline(cin, streetName);
                        cout << "Enter House Number: ";
                        getline(cin, houseNo);

                        cout << "Enter Occupation: ";
                        getline(cin, occupation);

                        popModule.addPerson(cnic, name, age, occupation, sectorName, streetName, houseNo);


                        break;
                    }
                case '2':
                    {
                        // Find Person
                        string cnic;
                        cout << "Enter CNIC to Find Person: ";
                        getline(cin, cnic);
                        if(!UTIL::validateCNIC(cnic))
                        {
                            cout << "Invalid CNIC format." << endl;
                            break;
                        }
                        Population::People* p = popModule.findPerson(cnic);
                        if(p){
                            cout << "Person Found: " << p->name << endl;
                            cout << "Details:" << endl;
                            cout << "CNIC: " << p->CNIC << endl;
                            cout << "Age: " << p->age << endl;
                            cout << "Occupation: " << p->occupation << endl;
                            cout << "Sector: " << (p->sector ? p->sector->name : "N/A") << endl;
                            cout << "Street: " << (p->street ? p->street->name : "N/A") << endl;
                            cout << "House: " << (p->house ? p->house->houseNo : "N/A") << endl;
                        }
                        else
                            cout << "Person with CNIC '" << cnic << "' not found." << endl;

                        break;
                    }
                case '3':
                    {
                        // Print Family Tree
                        string cnic;
                        cout << "Enter CNIC to Print Family Tree: ";
                        getline(cin, cnic);
                        if(!UTIL::validateCNIC(cnic))
                        {
                            cout << "Invalid CNIC format." << endl;
                            break;
                        }
                        popModule.printFamilyTree(cnic);
                        break;
                    }
                case '4':
                    {
                        // Assign Relations
                        cout << "What type of relation do you want to assign?" << endl;
                        cout << "1. Father" << endl;
                        cout << "2. Mother" << endl;
                        cout << "3. Spouse" << endl;
                        cout << "4. Child" << endl;
                        cout << "5. Sibling" << endl;
                        cout << "Enter your choice: ";
                        char relationChoice;
                        cin >> relationChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        string cnic1, cnic2;
                        cout << "Enter CNIC of First Person: ";
                        getline(cin, cnic1);
                        while(!UTIL::validateCNIC(cnic1))
                        {
                            cout << "Invalid CNIC format. Please re-enter: ";
                            getline(cin, cnic1);
                        }
                        cout << "Enter CNIC of Second Person: ";
                        getline(cin, cnic2);
                        while(!UTIL::validateCNIC(cnic2))
                        {
                            cout << "Invalid CNIC format. Please re-enter: ";
                            getline(cin, cnic2);
                        }
                        Population::People* p1 = popModule.findPerson(cnic1);
                        Population::People* p2 = popModule.findPerson(cnic2);
                        if(!p1 || !p2)
                        {
                            cout << "One or both persons not found." << endl;
                            break;
                        }

                        switch(relationChoice)
                        {
                            case '1':
                                popModule.relations()->setFather(cnic1, cnic2);
                                cout << "Assigned Father relation." << endl;
                                break;
                            case '2':
                                popModule.relations()->setMother(cnic1, cnic2);
                                cout << "Assigned Mother relation." << endl;
                                break;
                            case '3':
                                popModule.relations()->setSpouse(cnic1, cnic2);
                                cout << "Assigned Spouse relation." << endl;
                                break;
                            case '4':
                                popModule.relations()->addChild(cnic1, cnic2);
                                cout << "Assigned Child relation." << endl;
                                break;
                            case '5':
                                popModule.relations()->addSibling(cnic1, cnic2);
                                cout << "Assigned Sibling relation." << endl;
                                break;
                            default:
                                cout << "Invalid relation choice." << endl;
                                break;
                        }
                        break;
                    }
                case '5':
                    {
                        // Total Residents in a House
                        string sectorName, streetName, houseNo;
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);
                        if(!sectorGraph.searchSector(sectorName))
                        {
                            cout << "Sector '" << sectorName << "' does not exist." << endl;
                            break;
                        }
                        cout << "Enter Street Name: ";
                        getline(cin, streetName);
                        if(!popModule.findStreet(popModule.findSector(sectorName), streetName))
                        {
                            cout << "Street '" << streetName << "' does not exist in Sector '" << sectorName << "'." << endl;
                            break;
                        }

                        cout << "Enter House Number: ";
                        getline(cin, houseNo);
                        if(!popModule.findHouse(popModule.findStreet(popModule.findSector(sectorName), streetName), houseNo))
                        {
                            cout << "House '" << houseNo << "' does not exist on Street '" << streetName << "' in Sector '" << sectorName << "'." << endl;
                            break;
                        }


                        int count = popModule.populationByHouse(sectorName, streetName, houseNo);
                        cout << "Total Residents in House '" << houseNo << "' on Street '" << streetName << "' in Sector '" << sectorName << "': " << count << endl;
                        break;
                    }
                case '6':
                    {
                        // Total Population in a street
                        string sectorName, streetName;
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);
                        if(!sectorGraph.searchSector(sectorName))
                        {
                            cout << "Sector '" << sectorName << "' does not exist." << endl;
                            break;
                        }
                        cout << "Enter Street Name: ";
                        getline(cin, streetName);
                        if(!popModule.findStreet(popModule.findSector(sectorName), streetName))
                        {
                            cout << "Street '" << streetName << "' does not exist in Sector '" << sectorName << "'." << endl;
                            break;
                        }
                        int count = popModule.populationByStreet(sectorName, streetName);
                        cout << "Total Population on Street '" << streetName << "' in Sector '" << sectorName << "': " << count << endl;

                        break;
                    }
                case '7':
                    {
                        // Total Population in a sector
                        string sectorName;
                        cout << "Enter Sector Name: ";
                        getline(cin, sectorName);
                        if(!sectorGraph.searchSector(sectorName))
                        {
                            cout << "Sector '" << sectorName << "' does not exist." << endl;
                            break;
                        }
                        int count = popModule.populationBySector(sectorName);
                        cout << "Total Population in Sector '" << sectorName << "': " << count << endl;

                        break;
                    }
                case '8':
                    {
                        // Total Population in the City
                        int count = popModule.totalPopulation();
                        cout << "Total Population in the City: " << count << endl;
                        break;
                    }
                case '9':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '9' );
    }

    void busModule()
    {
        char input = 1;

        do
        {
            printTransportMenu();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
                case '1':
                {
                    // Print Comapnies
                    transportModule.printCompanies();
                    break;
                }
                case '2':
                {
                    // Print Buses
                    string busNo;
                    cout << "Enter Bus Number to Display: ";
                    getline(cin, busNo);
                    transportModule.displayBus(busNo);
                    break;
                }
                case '3':
                {
                    // Stop by ID
                    string stopID;
                    cout << "Enter Bus Stop ID to Lookup: ";
                    getline(cin, stopID);
                    BusStop* stop = transportModule.getStopByID(stopID);
                    if (stop)
                    {
                        cout << "Bus Stop Found: " << stop->getName() << " in Sector " << stop->getSectorName() << endl;
                    }
                    else
                    {
                        cout << "Bus Stop with ID '" << stopID << "' not found." << endl;
                    }
                    break;
                }

                case '4':
                {
                    // Nearest Bus to Stop
                    string stopID;
                    cout << "Enter Bus Stop ID to Find Nearest Bus: ";
                    getline(cin, stopID);
                    Bus* bus = transportModule.nearestBusToStop(stopID);
                    if(bus)
                    {
                        cout << "Nearest Bus is '" << bus->getBusNo() << "' from Company '" << bus->getCompany() << "'." << endl;
                    }
                    else
                    {
                        cout << "No buses found near Stop ID '" << stopID << "'." << endl;
                    }
                    break;
                }

                case '5':
                {
                    // Shortest Path between Stops
                    string stopA, stopB;
                    cout << "Enter Starting Bus Stop ID: ";
                    getline(cin, stopA);
                    cout << "Enter Destination Bus Stop ID: ";
                    getline(cin, stopB);
                    if(transportModule.shortestPath(stopA, stopB))
                    {
                        cout << "Shortest path calculated between '" << stopA << "' and '" << stopB << "'." << endl;
                    }
                    else
                    {
                        cout << "Failed to find shortest path between '" << stopA << "' and '" << stopB << "'." << endl;
                    }
                    break;
                }

                case '6':
                {
                    // Emergency Route
                    string busNo, destStopID;
                    cout << "Enter Bus Number for Emergency Route: ";
                    getline(cin, busNo);
                    Bus* bus = transportModule.getBusByID(busNo);
                    if(!bus)
                    {
                        cout << "Bus with Number '" << busNo << "' not found." << endl;
                        break;
                    }

                    cout << "Enter Emergency Destination Stop: ";
                    getline(cin, destStopID);
                    BusStop* destStop = transportModule.getStopByID(destStopID);
                    if(!destStop)
                    {
                        cout << "Destination Stop with ID '" << destStopID << "' not found." << endl;
                        break;
                    }
                    transportModule.emergencyRoute(busNo, destStopID);
                    break;
                }

                case '7':
                {
                    // Bus Simulation
                    string busNo;
                    cout << "Enter Bus Number to Simulate Movement: ";
                    getline(cin, busNo);
                    Bus* bus = transportModule.getBusByID(busNo);
                    if(!bus)
                    {
                        cout << "Bus with Number '" << busNo << "' not found." << endl;
                        break;
                    }

                    cout << "\n--- Before Movement ---" << endl;
                    transportModule.displayBus(busNo);
                    transportModule.simulateBusMovement(busNo);
                    cout << "\n--- After Movement ---" << endl;
                    transportModule.displayBus(busNo);
                    break;
                }

                case '8':
                {
                    // New company
                    string companyName;
                    cout << "Enter New Bus Company Name to Register: ";
                    getline(cin, companyName);
                    string busNo;
                    cout << "Enter Bus Number for the New Company: ";
                    getline(cin, busNo);

                    if(transportModule.getBusByID(busNo))
                    {
                        cout << "Bus with Number '" << busNo << "' already exists." << endl;
                        break;
                    }

                    Bus* newBus = new Bus(busNo, companyName);
                    transportModule.addBus(newBus);
                    transportModule.registerCompany(companyName);
                    break;
                }


                case '9':
                {
                    //school
                    transportModule.registerSchoolBusInteractive(&educationModule);
                    break;
                }

                case 'A':
                {
                    //track bus route
                    string busNo;
                    cout << "Enter Bus Number to Track Route: ";
                    getline(cin, busNo);
                    Bus* bus = transportModule.getBusByID(busNo);
                    if(!bus)
                    {
                        cout << "Bus with Number '" << busNo << "' not found." << endl;
                        break;
                    }
                    bus->trackRoute();
                    break;
                }
                
                case 'B':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '11' );
    }


    void pharmaModule()
    {
        char intput = 1;

        do
        {
            printPharmacyMenu();
            cout << "Enter your choice: ";
            cin >> intput;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(intput)
            {
                case '1':
                    {
                       // display all pharm
                        pharmacyModule.displayAllPharmacies();
                        break;
                    }

                case '2':
                {
                    // search medicine by name
                    string medicineName;
                    cout << "Enter Medicine Name to Search: ";
                    getline(cin, medicineName);
                    string pharmacyName;
                    Medicine result;
                    if(pharmacyModule.searchMedicineByName(medicineName, pharmacyName, result))
                    {
                        cout << "Medicine Found in Pharmacy '" << pharmacyName << "': " << result << endl;
                    }
                    else
                    {
                        cout << "Medicine '" << medicineName << "' not found in any pharmacy." << endl;
                    }
                    break;
                }

                case '3':
                {
                    // medicine by formula
                    string formula;
                    cout << "Enter Medicine Formula to Search: ";
                    getline(cin, formula);
                    string pharmacyName;
                    Medicine result;
                    if(pharmacyModule.searchMedicineByFormula(formula, pharmacyName, result))
                    {
                        cout << "Medicine Found in Pharmacy '" << pharmacyName << "': " << result << endl;
                    }
                    else
                    {
                        cout << "No medicine found with formula '" << formula << "' in any pharmacy." << endl;
                    }
                    break;
                }

                case '4':
                {
                    // pharm details
                    string pharmacyName;
                    cout << "Enter Pharmacy Name to Display Details: ";
                    getline(cin, pharmacyName);
                    pharmacyModule.displayPharmacyDetails(pharmacyName);
                    break;
                }

                case '5':
                {
                    // add new pharm
                    string id, name, sector;
                    cout << "Enter Pharmacy ID: ";
                    getline(cin, id);
                    cout << "Enter Pharmacy Name: ";
                    getline(cin, name);
                    cout << "Enter Sector Name: ";
                    getline(cin, sector);
                    if(!sectorGraph.searchSector(sector))
                    {
                        cout << "Sector '" << sector << "' does not exist. Please add it first." << endl;
                        break;
                    }
                    sectorGraph.addFacility(sector, id, name, Facility::PHARMACY);
                    Pharmacy* newPharm = new Pharmacy(id, name, sector);
                    pharmacyModule.addPharmacy(newPharm);
                    pharmacyModule.buildPharmacyGraph(sectorGraph); // rebuild graph
                    cout << "Pharmacy '" << name << "' added successfully." << endl;
                    break;
                }

                case '6':
                {
                    // search pharm by name
                    string name;
                    cout << "Enter Pharmacy Name to Search: ";
                    getline(cin, name);
                    Pharmacy* pharm = pharmacyModule.findPharmacyByName(name);
                    if(pharm)
                    {
                        cout << "Pharmacy Found: ID='" << pharm->getPharmacyID() << "', Name='" << pharm->getName() << "', Sector='" << pharm->getSector() << "'" << endl;
                    }
                    else
                    {
                        cout << "Pharmacy with Name '" << name << "' not found." << endl;
                    }
                    break;
                }

                case '7':
                {
                    // find nearest pharm
                    string fromPharmacyName;
                    cout << "Enter Your Current Pharmacy Name: ";
                    getline(cin, fromPharmacyName);
                    Pharmacy* nearest = pharmacyModule.findNearestPharmacy(fromPharmacyName);
                    if(nearest)
                        cout << "Nearest Pharmacy is '" << nearest->getName() << "' in Sector '" << nearest->getSector() << "'." << endl;
                    else
                        cout << "No nearest Pharmacy found." << endl;
                    break;
                }

                case '8':
                {
                    // add medicine to pharm
                    string pharmacyID, medName, formula;
                    double price;
                    cout << "Enter Pharmacy ID to Add Medicine In: ";
                    getline(cin, pharmacyID);
                    if(!pharmacyModule.findPharmacyByID(pharmacyID))
                    {
                        cout << "Pharmacy with ID '" << pharmacyID << "' not found." << endl;
                        break;
                    }
                    cout << "Enter Medicine Name: ";
                    getline(cin, medName);
                    cout << "Enter Medicine Formula: ";
                    getline(cin, formula);
                    cout << "Enter Medicine Price: ";
                    cin >> price;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pharmacyModule.addMedicineToPharmacy(pharmacyID, medName, formula, price);
                    cout << "Medicine '" << medName << "' added to Pharmacy ID '" << pharmacyID << "' successfully." << endl;
                    break;
                }

                case '9':
                {
                    // Exit Module
                    system("cls");
                    cout << "Returning to Main Menu." << endl;
                    return;
                }

                
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (intput != '9' );

    }

    void medicalModule()
    {
        char input = 1;

        do
        {
            printHospitalModule();
            cout << "Enter your choice: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(input)
            {
                case '1':
                    {
                        // display all hospitals
                        hospitalModule.displayAllHospitals();
                        break;
                    }
                
                case '2':
                {
                    // Display Emergency Bed Status
                    hospitalModule.displayEmergencyBedStatus();
                    break;
                }

                case '3':
                {
                    // register doctor
                    string hospitalName, doctorID, doctorName, specialization;
                    cout << "Enter Hospital Name to Register Doctor In: ";
                    getline(cin, hospitalName);
                    if(!hospitalModule.findHospitalByName(hospitalName))
                    {
                        cout << "Hospital with Name '" << hospitalName << "' not found." << endl;
                        break;
                    }
                    cout << "Enter Doctor ID: ";
                    getline(cin, doctorID);
                    cout << "Enter Doctor Name: ";
                    getline(cin, doctorName);
                    cout << "Enter Doctor Specialization: ";
                    getline(cin, specialization);
                    hospitalModule.registerDoctorToHospital(hospitalName, doctorID, doctorName, specialization);
                    break;
                }

                case '4':
                {
                     // add patient
                    string hospitalName;
                    cout << "Enter Hospital Name to Add Patient In: ";
                    getline(cin, hospitalName);
                    if(!hospitalModule.findHospitalByName(hospitalName))
                    {
                        cout << "Hospital with Name '" << hospitalName << "' not found." << endl;
                        break;
                    }
                    string patientNam;
                    int priorityLevel;
                    cout << "Enter Patient Name: ";
                    getline(cin, patientNam);
                    cout << "Enter Patient Priority Level (1-10): ";
                    cin >> priorityLevel;
                    while(priorityLevel < 1 || priorityLevel > 10)
                    {
                        cout << "Invalid priority level. Please enter a value between 1 and 10: ";
                        cin >> priorityLevel;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Patient newPatient(patientNam, priorityLevel);
                    hospitalModule.addPatientToHospital(hospitalName, newPatient);
                    break;
                }

                case '5':
                {
                    // display details
                    string hospitalName;
                    cout << "Enter Hospital Name to Display Details: ";
                    getline(cin, hospitalName);
                    hospitalModule.displayHospitalDetails(hospitalName);
                    break;
                }
                
                case '6':
                {
                    // nearest hospital
                    string fromHospitalName;
                    cout << "Enter Your Current Hospital Name: ";
                    getline(cin, fromHospitalName);
                    Hospital* nearest = hospitalModule.findNearestHospital(fromHospitalName);
                    if(nearest)
                        cout << "Nearest Hospital is '" << nearest->getName() << "' in Sector '" << nearest->getSector() << "'." << endl;
                    else
                        cout << "No nearest Hospital found." << endl;
                    break;
                }

                case '7':
                {
                    // update beds
                    string hospitalName;
                    cout << "Enter Hospital Name to Update Beds In: ";
                    getline(cin, hospitalName);
                    if(!hospitalModule.findHospitalByName(hospitalName))
                    {
                        cout << "Hospital with Name '" << hospitalName << "' not found." << endl;
                        break;
                    }
                    int newBedCount;
                    cout << "Enter New Emergency Bed Count: ";
                    cin >> newBedCount;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    hospitalModule.updateHospitalBeds(hospitalName, newBedCount);
                    cout << "Updated Emergency Bed Count for Hospital '" << hospitalName << "' to " << newBedCount << "." << endl;
                    break;
                }

                case '8':
                {
                    // search by speci
                    string specialization;
                    cout << "Enter Specialization to Search Hospitals: ";
                    getline(cin, specialization);
                    hospitalModule.searchBySpecialization(specialization);
                    break;
                }

                case '9':
                {
                    // total beds
                    int totalBeds = hospitalModule.getTotalBeds();
                    cout << "Total Emergency Beds across all Hospitals: " << totalBeds << endl;
                    break;
                }

                case 'A':
                {
                    // average beds
                    int avgBeds = hospitalModule.getAverageBeds();
                    cout << "Average Emergency Beds per Hospital: " << avgBeds << endl;
                    break;
                }

                case 'B':
                    {
                        // Exit Module
                        system("cls");
                        cout << "Returning to Main Menu." << endl;
                        return;
                    }

                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");

        } while (input != '11' );
    }
public:
    CityManager()
    {
        // Global City Graph Network Initialization
        sectorGraph.loadCSV("dataset/sectors.csv");
        sectorGraph.loadFacilitiesFromCSV("dataset/schools.csv", Facility::EDUCATION);
        sectorGraph.loadFacilitiesFromCSV("dataset/pharmacies.csv", Facility::PHARMACY);
        sectorGraph.loadFacilitiesFromCSV("dataset/hospitals.csv", Facility::MEDICAL);


        // Education Module Initialization
        educationModule.loadSchoolsFromCSV("dataset/schools.csv", sectorGraph);
        educationModule.buildSchoolGraph(sectorGraph);

        // Public Module Initialization
        // Doesnt require loading from CSV as no dataset provided
        publicModule.buildSubgraph(sectorGraph);

        // Transport Module Initialization
        transportModule.setCityGraph(&sectorGraph);
        transportModule.loadStopsCSV("dataset/stops.csv");
        transportModule.loadBusesCSV("dataset/buses.csv", &educationModule);
        transportModule.buildTransportSubGraph();


        // Commercial Module Initialization
        commercialModule.buildMallGraph(sectorGraph);        

        // Population Module Initialization
        popModule.syncSectorsFromGraph(sectorGraph);
        popModule.loadCSVData("dataset/population.csv");


        // Medical Modules Initialization
        pharmacyModule.loadPharmaciesFromCSV("dataset/pharmacies.csv", sectorGraph);
        pharmacyModule.buildPharmacyGraph(sectorGraph);

        // Hospital Module Initialization
        hospitalModule.loadHospitalsFromCSV("dataset/hospitals.csv", sectorGraph);
        hospitalModule.buildHospitalGraph(sectorGraph);

    }



    void start()
    {
        system("cls");
        char input = 1;

        do
        {
            printMainMenu();
            cout << "Enter your choice: ";
            cin >> input;

            switch(input)
            {
            case '1':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Education Module Selected." << endl;
                        schoolsModule();
                        break;
                    }
                    case '2':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Public Facilities Module Selected." << endl;
                        publicFacilitiesModule();
                        break;
                    }
                

                case '3':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Map Module Selected." << endl;
                        mapModule();
                        break;
                    }

                case '4':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Population Module Selected." << endl;
                        peopleModule();
                        break;
                    }
                case '5':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Commercial Module Selected." << endl;
                        mallModule();
                        break;
                    }

                case '6':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Transport Module Selected." << endl;
                        busModule();
                        break;
                    }

                case '7':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Pharmacy Module Selected." << endl;
                        pharmaModule();
                        break;
                    }

                case '8':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Hospital Module Selected." << endl;
                        medicalModule();
                        break;
                    }
                case '9':
                    {
                        system("cls"); // clear console for next menu display
                        cout << "Exiting City Management System. Goodbye!" << endl;
                        break;
                    }
                default:
                    {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
            }

           

        } while (input != '9' );

    }

};
