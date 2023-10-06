/* 
다음의 함수를 applyShipping과 caclculatingPricingData로 
두함수로 분리하여 단계를 분리하여라 
*/

function applyShipping(priceData, shippingMethod){
	const shippingPerCase = (priceData.basePrice > shippingMethod.discountThreshold) ?
		shippingMethod.discountedFee : shippingMethod.feePerCase;
	const shippingCost = priceData.quantity * shippingPerCase;
	const price = priceData.basePrice - priceData.discount + shippingCost;
	return price
}

function calculatePricingData(product, quantity){
	const basePrice = product.basePrice * quantity;
	const discount = Math.max(quantity - product.discountThreshold, 0)
		* product.basePrice * product.discountrate;

	return {basePrice, quantity, discount}	
}

function priceOrder(product, quantity, shippingMethod){
	const priceData = calculatePricingData(product, quantity)
	return applyShipping(priceData, shippingMethod);;
}



product = {basePrice: 3000, discountThreshold : 150, discountrate : 0.02};
quantity = 300;
shippingMethod = {discountThreshold : 150000, discountedFee : 1000, feePerCase: 2500}
console.log(priceOrder(product, quantity, shippingMethod));