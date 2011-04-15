/*
 * DisambigCustomizedDefs.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: ysun
 */

#include "DisambigCustomizedDefs.h"

template <> const string cAttribute_Intermediary<cFirstname>::class_name = "Firstname";
template <> const string cAttribute_Intermediary<cFirstname>::attrib_group = "Personal";


template <> const string cAttribute_Intermediary<cLastname>::class_name = "Lastname";
template <> const string cAttribute_Intermediary<cLastname>::attrib_group = "Personal";

template <> const string cAttribute_Intermediary<cMiddlename>::class_name = "Middlename";
template <> const string cAttribute_Intermediary<cMiddlename>::attrib_group = "Personal";

template <> const string cAttribute_Intermediary<cLatitude>::class_name = "Latitude";
template <> const string cAttribute_Intermediary<cLatitude>::interactive_column_names[] = {"Longitude", "Street", "Country"};
template <> const unsigned int cAttribute_Intermediary<cLatitude>::num_of_interactive_columns = 3;
template <> const string cAttribute_Intermediary<cLatitude>::attrib_group = "Patent";


template <> const string cAttribute_Intermediary<cLongitude>::class_name = "Longitude";

template <> const string cAttribute_Intermediary<cStreet>::class_name = "Street";


template <> const string cAttribute_Intermediary<cCountry>::class_name = "Country";
//template <> const string cAttribute_Intermediary<cCountry>::attrib_group = "Patent";

template <> const string cAttribute_Intermediary<cClass>::class_name = "Class";
template <> const string cAttribute_Intermediary<cClass>::attrib_group = "Patent";

template <> const string cAttribute_Intermediary<cClass_M2>::class_name = "Class_Measure2";
template <> const string cAttribute_Intermediary<cClass_M2>::attrib_group = "Patent";


template <> const string cAttribute_Intermediary<cCoauthor>::class_name = "Coauthor";
template <> const string cAttribute_Intermediary<cCoauthor>::attrib_group = "Patent";

template <> const string cAttribute_Intermediary<cAssignee>::class_name = "Assignee";
template <> const string cAttribute_Intermediary<cAssignee>::interactive_column_names[] = {"AsgNum"};
template <> const unsigned int cAttribute_Intermediary<cAssignee>::num_of_interactive_columns = 1;
const map<string, std::pair<string, unsigned int>  > * cAssignee::assignee_tree_pointer;
template <> const string cAttribute_Intermediary<cAssignee>::attrib_group = "Patent";

template <> const string cAttribute_Intermediary<cAsgNum>::class_name = "AsgNum";

template <> const string cAttribute_Intermediary<cUnique_Record_ID>::class_name = "Unique_Record_ID";

template <> const string cAttribute_Intermediary<cApplyYear>::class_name = "ApplyYear";

template <> const string cAttribute_Intermediary<cCity>::class_name = "City";

template <> const string cAttribute_Intermediary<cPatent>::class_name = "Patent";




bool cFirstname::split_string(const char *inputdata) {
	static const char delim = ' ';
	cAttribute::split_string(inputdata);
	const string * psource = get_data().at(0);
	const size_t pos = psource->find(delim);
	vector < const string * > & data_alias = get_data_modifiable();
	if ( pos == string::npos )
		data_alias.push_back(psource);
	else {
		string to_push ( psource->begin(), psource->begin() + pos );
		data_alias.push_back(this->add_string( to_push) );
	}
	return true;
}

/*
unsigned int cFirstname::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		unsigned int res = 0;
		const cFirstname & rhs = dynamic_cast< const cFirstname & > (right_hand_side);
		//for (vector <string>::const_iterator p = this->get_data().begin(); p != this->get_data().end(); ++p ) {
		//	for (vector <string>::const_iterator q = rhs.get_data().begin(); q != rhs.get_data().end(); ++q ) {
		//		unsigned int temp_res = jwcmp(*p, *q);
		//		res = ( res < temp_res ) ? temp_res : res ;
		//	}
		//}

		res = jwcmp(* this->get_data().at(1), * rhs.get_data().at(1));
		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}
*/

#if 0
unsigned int cLastname::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		unsigned int res = 0;
		const cLastname & rhs = dynamic_cast< const cLastname & > (right_hand_side);
		//for (vector <string>::const_iterator p = this->get_data().begin(); p != this->get_data().end(); ++p ) {
		//	for (vector <string>::const_iterator q = rhs.get_data().begin(); q != rhs.get_data().end(); ++q ) {
		//		unsigned int temp_res = jwcmp(*p, *q);
		//		res = ( res < temp_res ) ? temp_res : res ;
		//	}
		//}

		res = jwcmp( * this->get_data().at(0), * rhs.get_data().at(0));
		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}
#endif

bool cMiddlename::split_string(const char *inputdata) {
	//static const string impossible_label = "@";
	cAttribute::split_string(inputdata);
	const string & source = * get_data().at(0);
	size_t pos = source.find(' ');
	string midpart;
	if ( pos == string::npos )
		midpart = "";
	else
		midpart = source.substr( pos + 1 );

	char initials[50];
	extract_initials(initials, midpart.c_str());
	//if ( ! midpart.empty())
	//	midpart = impossible_label + midpart;
	const char * start = initials;
	//if ( initials[0] == '\0' )
	//	start = initials;
	//else
	//	start = initials + 1;
	vector < const string * > & data_alias = get_data_modifiable();
	string temp(start);
	data_alias.clear();
	data_alias.push_back(this->add_string( midpart) );
	data_alias.push_back(this->add_string( temp ) );
	return true;
}

unsigned int cMiddlename::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		//unsigned int res = 0;
		const cMiddlename & rhs = dynamic_cast< const cMiddlename & > (right_hand_side);
		//for (vector <string>::const_iterator p = this->get_data().begin(); p != this->get_data().end(); ++p ) {
		//	for (vector <string>::const_iterator q = rhs.get_data().begin(); q != rhs.get_data().end(); ++q ) {
				//unsigned int temp_res = midnamecmp(*p, *q);
				//res = ( res < temp_res ) ? temp_res : res ;
		//	}
		//}
		unsigned int res = midnamecmp(* this->get_data().at(0), * rhs.get_data().at(0));
		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}


unsigned int cLatitude::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		unsigned int res = 0;
		const cLatitude & rhs = dynamic_cast< const cLatitude & > (right_hand_side);

		const cAttribute* const & this_longitude = this->get_interactive_vector().at(0);
		const cAttribute* const & rhs_longitude = rhs.get_interactive_vector().at(0);
		if ( this->get_data().size() != this_longitude->get_data().size() ) {
			std::cout << "Alignment error in latitude comparison: " << std::endl;
			this->print(std::cout);
			this_longitude->print(std::cout);
			throw cException_Interactive_Misalignment(this->get_class_name().c_str());
		}
		if ( rhs.get_data().size() != rhs_longitude->get_data().size() ) {
			std::cout << "Alignment error in latitude comparison: " << std::endl;
			rhs.print(std::cout);
			rhs_longitude->print(std::cout);
			throw cException_Interactive_Misalignment(this->get_class_name().c_str());
		}



		//latitude interacts with		{"Longitude", "Street", "Country"}; the sequence is important.
		vector <const string* >::const_iterator p, q;

		// Comparing country
		unsigned int country_score = 0;
		if ( this->get_interactive_vector().at(2) == rhs.get_interactive_vector().at(2) )
			country_score = 1;

		// Comparing street;
		//unsigned int street_score = 0;

		// Comparing Latitidue and longitude
		unsigned int latlon_score = 0;

		latlon_score = latloncmp ( * this->get_data().at(0), * this->get_interactive_vector().at(0)->get_data().at(0),
									* rhs.get_data().at(0), * rhs.get_interactive_vector().at(0)->get_data().at(0) );

		if ( country_score == 0 )
			res = 0;
		else
			res = latlon_score;


		/*
		const string * p1 = this->get_data().front();
		const string * q1 = this->get_interactive_vector().at(0)->get_data().front();
		const string * p2 = rhs.get_data().front();
		const string * q2 = rhs.get_interactive_vector().at(0)->get_data().front();

		if ( ( ! p1->empty() && !p2->empty() && p1 != p2 ) || ( !q1->empty() && ! q2->empty() && q1 != q2 ) )
			res = 0;
		else if ( ( ! p1->empty() && !p2->empty() && p1 == p2 ) && ( !q1->empty() && ! q2->empty() && q1 == q2 ) )
			res = 2;
		else
			res = 1;
		 */

		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}

#if 0
bool cClass::split_string(const char* inputdata) {
	try {
		cAttribute::split_string(inputdata);
	}
	catch ( const cException_Vector_Data & except) {
		//std::cout << "cClass allows vector data. This info should be disabled in the real run." << std::endl;
	}
	const string raw(inputdata);
	this->set_class.clear();
	this->set_class.insert(this->get_data().begin(), this->get_data().end());
	this->get_data_modifiable().clear();
	//this->get_data_modifiable().insert(this->get_data_modifiable().begin(), this->add_string(raw));
	return true;
}

const cClass * cClass::attrib_merge ( const cAttribute & right_hand_side) const {
	try {
		const cClass & rhs = dynamic_cast< const cClass & > (right_hand_side);
		set < const string * > temp (this->set_class);
		temp.insert(rhs.set_class.begin(), rhs.set_class.end());
		cClass tempclass;
		tempclass.set_class = temp;
		const cClass * result = this->static_add_attrib(tempclass, 2);
		cClass::static_reduce_attrib(*this, 1);
		cClass::static_reduce_attrib(rhs, 1);
		return result;

	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}

}

#endif

#if 0
unsigned int cClass::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {

		unsigned int res = 0;
		const cClass & rhs = dynamic_cast< const cClass & > (right_hand_side);
		/*
		vector <const string*>::const_iterator p = this->get_data().begin();
		for ( ++p ; p != this->get_data().end(); ++p ) {
			vector < const string*>::const_iterator q = rhs.get_data().begin();
			for ( ++q ; q != rhs.get_data().end(); ++q ) {
				unsigned int temp_res = classcmp(**p, **q);
				res += temp_res;
			}
		}
		*/

		const unsigned int cnt  = num_common_elements (this->attrib_set.begin(), this->attrib_set.end(),
								 	 rhs.attrib_set.begin(), rhs.attrib_set.end(), 0 );
		const double score = 1.0 * cnt * cnt / this->attrib_set.size() / rhs.attrib_set.size();

		if ( score > 0.1 )
			++res;
		if ( score > 0.2 )
			++res;
		if ( score > 0.3 )
			++res;
		if ( score > 0.4 )
			++res;

		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}
#endif


#if 0
bool cCoauthor::split_string(const char* inputdata) {

	try {
		cAttribute::split_string(inputdata);
	}
	catch ( const cException_Vector_Data & except) {
		//std::cout << "cClass allows vector data. This info should be disabled in the real run." << std::endl;
	}
	//const string raw(inputdata);
	this->attrib_set.clear();
	for ( vector < const string *>::const_iterator p = this->get_data().begin(); p != this->get_data().end(); ++p ) {
		if ( (*p)->empty() )
			continue;
		this->attrib_set.insert(*p);
	}
	this->get_data_modifiable().clear();
	//this->get_data_modifiable().insert(this->get_data_modifiable().begin(), this->add_string(raw));
	return true;
}




unsigned int cCoauthor::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		unsigned int res = 0;
		const cCoauthor & rhs = dynamic_cast< const cCoauthor & > (right_hand_side);
		//for (vector <string>::const_iterator p = this->get_data().begin(); p != this->get_data().end(); ++p ) {
			//for (vector <string>::const_iterator q = rhs.get_data().begin(); q != rhs.get_data().end(); ++q ) {
				//unsigned int temp_res = coauthorcmp(*p, *q);
				//res += temp_res;
			//}
		//}
		/*
		const bool scan_left_tree = this->pset->size() > rhs.pset->size();
		const set< const string * > * ps, *qs;
		ps = qs = NULL;
		if ( scan_left_tree ) {
			ps = this->pset;
			qs = rhs.pset;
		}
		else {
			qs = this->pset;
			ps = rhs.pset;
		}

		for ( set< const string* >::const_iterator p = qs->begin(); p != qs->end(); ++p ) {
			if ( ps->find(*p) != ps->end())
				++res;
		}
		*/

		res = num_common_elements (this->attrib_set.begin(), this->attrib_set.end(),
									 rhs.attrib_set.begin(), rhs.attrib_set.end(),
									 this->max_value);



		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}

#endif
#if 0
bool cAssignee::split_string(const char* inputdata) {
	cAttribute::split_string(inputdata);
	static const char delim = ' ';
	const char * const pend = inputdata + strlen(inputdata);
	const char * pos, * prev_pos;
	pos = prev_pos = inputdata;
	vector < const string *> & data_ref = this->get_data_modifiable();
	do {
		pos = std::find( prev_pos, pend, delim);
		string temp ( prev_pos, pos );
		data_ref.push_back( this->add_string( temp ) );
		prev_pos = pos + 1;
	} while ( pos != pend);
	return true;
}
#endif


unsigned int cClass_M2::compare(const cAttribute & right_hand_side) const {
	const cClass_M2 & rhs = dynamic_cast< const cClass_M2 & > (right_hand_side);
	const unsigned int common = this->cAttribute_Set_Mode <cClass_M2>::compare( rhs );
	const unsigned int this_size = this->attrib_set.size();
	const unsigned int rhs_size = rhs.attrib_set.size();

	const double factor = 1.0 * common * common / this_size / rhs_size;
	if ( factor > 0.3 )
		return 4;
	else if ( factor > 0.2 )
		return 3;
	else if ( factor > 0.1 )
		return 2;
	else if ( factor > 0.05 )
		return 1;
	else
		return 0;
}

unsigned int cCountry::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());

	if ( !this->is_informative() || ! right_hand_side.is_informative() )
		return 1;
	if ( this == & right_hand_side )
		return 2;
	else
		return 0;
}


unsigned int cAssignee::compare(const cAttribute & right_hand_side) const {
	if ( ! is_comparator_activated () )
		throw cException_No_Comparision_Function(static_get_class_name().c_str());
	try {
		if ( this == & right_hand_side )
			return max_value;

		const cAssignee & rhs = dynamic_cast< const cAssignee & > (right_hand_side);
		//unsigned int res = asgcmp(this->get_data(), rhs.get_data(), assignee_tree_pointer);
		unsigned int res = asgcmp_old ( * this->get_data().at(0), * rhs.get_data().at(0), assignee_tree_pointer);
		if ( res > max_value )
			res = max_value;
		return res;
	}
	catch ( const std::bad_cast & except ) {
		std::cerr << except.what() << std::endl;
		std::cerr << "Error: " << this->get_class_name() << " is compared to " << right_hand_side.get_class_name() << std::endl;
		throw;
	}
}

bool cCity::split_string(const char* source) {
	string temp (source);
	get_data_modifiable().push_back(this->add_string(temp));
	//data_count.push_back(1);
	return true;
}