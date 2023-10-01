

function printOwing(invoice){
	let outstanding = calculateOutstanding(invoice);

	printBanner();
	recordDueDate(invoice);
	printDetails(invoice, outstanding);

	function calculateOutstanding(invoice){
		let result = 0;
		for (const o of invoice.orders){
			result += o.amount;
		}
		return result;
	}

	function printBanner() {
		console.log("**************");
		console.log("고객 채무");
		console.log("**************");
	}

	function printDetails(invoice, outstanding){
		console.log(`고객명 : ${invoice.customer}`);
		console.log(`채무액 : ${outstanding}`)
		console.log(`마감일 : ${invoice.dueDate.toLocalDateString()}`)
	}
	function recordDueDate(invoice){
		// 마감일(dueDate)을 기록한다
		const today = Clock.today;
		invoice.dueDate = new Date(today.getFullYear(), today.getMounth(), today.getDate() + 30);
	}
}

