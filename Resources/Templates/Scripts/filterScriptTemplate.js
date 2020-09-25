/* ********** FILTER SPECIFIC SCRIPTING **********************

	The "local" variable refers to the object containing the scripts. In this case, the local variable refers to the filter.
	It means that you can access any control inside  this filter by accessing it through its address.
*/

/*
 This function will be called each time the filter is processed, and expects a return value.
 This function only exists because the script is in a filter
 The "inputValue" argument is an array of all the values that are being mapped.
*/
function filter(inputValue, min, max)
{
	var result = inputValue[0] * myFloatParam.get(); //Basic multiplication of the first input value by the script parameter myFloatParam
	return result;
}