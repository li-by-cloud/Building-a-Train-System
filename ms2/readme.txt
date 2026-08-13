Milestone #2
Milestone 2 implements and tests the CustomerOrder module.

The CustomerOrder module contains all the functionality for processing customer orders as they move from Station to Station along the assembly line. The Station where a given order currently rests fills a request for one item of that station, if there is any such request.

CustomerOrder Module
A CustomerOrder object manages a single order on the assembly line and contains the following information:

The CustomerOrder class has the following structure:

Item Definition

struct Item
{
	std::string m_itemName;
	size_t m_serialNumber{0};
	bool m_isFilled{false};

	Item(const std::string& src) : m_itemName(src) {};
};
Instance Variables

std::string m_name – the name of the customer (e.g., John, Sara, etc)
std::string m_product – the name of the product being assembled (e.g., Desktop, Laptop, etc)
size_t m_cntItem – a count of the number of items in the customer's order
Item** m_lstItem – a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item (see below). This is the resource that your class must manage.
Class Variable

static size_t m_widthField – the maximum width of a field, used for display purposes
Member Functions

default constructor

a custom 1-argument constructor that takes a reference to an unmodifiable string. This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance. The fields in the string are (separated by a delimiter):

Customer Name
Order Name
the list of items making up the order (at least one item)
After finishing extraction, this constructor updates CustomerOrder::m_widthField if the current value is smaller than the value stored in Utilities::m_widthField.

a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called and the copy operator= should be deleted.

a move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.

a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.

a destructor

bool isOrderFilled() const – returns true if all the items in the order have been filled; false otherwise

bool isItemFilled(const std::string& itemName) const – returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.

void fillItem(Station& station, std::ostream& os) – this modifier fills one item in the current order that the Station specified in the first parameter handles.

if the order doesn't contain the item handled, this function does nothing
if the order contains items handled, and the Station's inventory contains at least one item, this function fills the order with one single item. It subtracts 1 from the inventory and updates Item::m_serialNumber and Item::m_isFilled. It also prints the message     Filled NAME, PRODUCT [ITEM_NAME].
if the order contains items handled but unfilled, and the inventory is empty, this function prints the message     Unable to fill NAME, PRODUCT [ITEM_NAME].
all messages printed are terminated by an endline
void display(std::ostream& os) const – this query displays the state of the current object in the format (see the sample output for details)

CUSTOMER_NAME - PRODUCT
[SERIAL] ITEM_NAME - STATUS
[SERIAL] ITEM_NAME - STATUS
...
SERIAL - a field of width 6
ITEM_NAME - a field of size m_widthField
STATUS is either FILLED or TO BE FILLED
you must use IO manipulators to format this output.

output
========================================
=         Stations (summary)           =
========================================
001 | Armchair       | 654321 | 
002 | Bed            | 123456 | 
003 | Dresser        | 056789 | 
004 | Nighttable     | 000887 | 
005 | Filing Cabinet | 987654 | 
006 | Office Chair   | 147852 | 
007 | Bookcase       | 000987 | 
008 | Desk           | 459214 | 


========================================
=          Stations (full)             =
========================================
001 | Armchair       | 654321 |   10 | Upholstered Wing Chair
002 | Bed            | 123456 |    5 | Queen size bed with headboard
003 | Dresser        | 056789 |    7 | 6-Drawer Unit
004 | Nighttable     | 000887 |    5 | Nightstand with 2 drawers
005 | Filing Cabinet | 987654 |    5 | 3-drawer filing cabinet
006 | Office Chair   | 147852 |   20 | High-back carpet-rollers
007 | Bookcase       | 000987 |    5 | 5-shelf open bookcase
008 | Desk           | 459214 |    2 | 6-foot worktable


========================================
=          Manual Validation           =
========================================
getItemName(): Armchair
getNextSerialNumber(): 654321
getNextSerialNumber(): 654322
getQuantity(): 10
getQuantity(): 9


========================================
=              Utilities               =
========================================
Data: [a]    Delimiter: [a]
   ERROR: No token.
Data: [a]    Delimiter: [b]
   Token: [a] [1]
Data: [Hello]    Delimiter: [l]
   Token: [He] [2]
   ERROR: No token.
Data: [apple,orange,banana,kiwi,strawberry,yellow watermellon]    Delimiter: [,]
   Token: [apple] [5]
   Token: [orange] [6]
   Token: [banana] [6]
   Token: [kiwi] [6]
   Token: [strawberry] [10]
   Token: [yellow watermellon] [18]
Data: [Gengar|Arcanine|Bulbasaur|Blaziken|C h a r i z a r d|Umbreon|Lucario|Eevee]    Delimiter: [|]
   Token: [Gengar] [6]
   Token: [Arcanine] [8]
   Token: [Bulbasaur] [9]
   Token: [Blaziken] [9]
   Token: [C h a r i z a r d] [17]
   Token: [Umbreon] [17]
   Token: [Lucario] [17]
   Token: [Eevee] [17]
========================================
=                Orders                =
========================================
Cornel B. - 1-Room Home Office
[000000] Office Chair                   - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
Chris S. - Bedroom
[000000] Bed                            - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Dresser                        - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
John M. - Kids Bedroom
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Dresser                        - TO BE FILLED
[000000] Desk                           - TO BE FILLED
Hong H. - 1-Room Office
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
Rania A. - 2-Room Home Office and Bedroom
[000000] Desk                           - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Dresser                        - TO BE FILLED


========================================
=          Manual Validation           =
========================================
CustomerOrders::display(): Rania A. - 2-Room Home Office and Bedroom
[000000] Desk                           - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Dresser                        - TO BE FILLED

CustomerOrders::CustomerOrders(&): ----> ERROR: Cannot make copies.

CustomerOrders::CustomerOrders(&&): Rania A. - 2-Room Home Office and Bedroom
[000000] Desk                           - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Dresser                        - TO BE FILLED

CustomerOrders::CustomerOrders(string): Chloe - Flight PC
[000000] CPU                            - TO BE FILLED
[000000] GPU                            - TO BE FILLED
[000000] Power Supply                   - TO BE FILLED

CustomerOrders::operator=(&&): Hong H. - 1-Room Office
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED

CustomerOrders::fillItem()
isOrderFilled(): MISSING
isItemFilled("CPU"): FILLED
isOrderFilled(): MISSING
    Filled Hong H., 1-Room Office [Filing Cabinet]
    Filled Hong H., 1-Room Office [Office Chair]
    Filled Hong H., 1-Room Office [Bookcase]
    Filled Hong H., 1-Room Office [Desk]
isOrderFilled(): MISSING