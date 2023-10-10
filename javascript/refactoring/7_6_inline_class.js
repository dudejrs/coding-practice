/* TrackingInformation을 Shipment에 인라인하도록 하여라  */ 


// class TrackingInformation {

// 	constructor(data){
// 		this._shippingCompany = data.shippingCompany;
// 		this._trackingNumber = data.trackingNumber;
// 	}

// 	get shippingCompany() {return this._shippingCompany;}
// 	set shippingCompany(arg) {this._shippingCompany = arg;}
// 	get trackingNumber() {return this._trackingNumber;}
// 	set trackingNumber(arg) {this._trackingNumber = arg;}
// 	get display() {
// 		return `${this.shippingCompany}: ${this.trackingNumber}`;
// 	}
// }

class Shipment{

	constructor(data){
		// this._trackingInformation = new TrackingInformation(data);
		this._shippingCompany = data.shippingCompany;
		this._trackingNumber = data.trackingNumber;
	}

	get shippingCompany(){return this._shippingCompany;}
	set shippingCompany(arg){this._shippingCompany = arg;}
	get trackingNumber() {return this._trackingNumber;}
	set trackingNumber(arg) {this._trackingNumber = arg;}
	get trackingInfo() {
		return `${this.shippingCompany} : ${this.trackingNumber}`;
	}

	// get shippingCompany(){return this.trackingInformation.shippingCompany;}
	// set shippingCompany(arg){this.trackingInformation.shippingCompany = arg;}
	// get shippingCompany(){return this._shippingCompany;}
	// set shippingCompany(arg){this._shippingCompany = arg;}
	// get trackingInformation() {return this._trackingInformation;}
	// set trackingInformation(arg) {this._trackingInformation = arg;}

}

aShipment = new Shipment({
	trackingNumber : 123456789,
	shippingCompany : "대한통운"
});

request = { vendor : "한진택배"}
aShipment.shippingCompany = request.vendor;
console.log(aShipment.trackingInfo)





