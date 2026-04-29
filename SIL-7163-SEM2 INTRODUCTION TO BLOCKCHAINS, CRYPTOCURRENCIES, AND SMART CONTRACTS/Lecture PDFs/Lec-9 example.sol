// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract SimpleFaucet{

	 // Persistent storage of the contract 
	 address public owner;
	 bool public paused;
	 uint256 public dripAmountWei;
	 uint256 public cooldownSeconds;
	 mapping(address => uint256) public lastClaimAt;

	 // Log emitting events -- stored where? Persistent? 
	 event Deposited(address indexed from, uint256 amount);
	 event Claimed(address indexed to, uint256 amount);
	 event Paused(bool paused);
	 event ParamsUpdated(uint256 dripAmountWei, uint256 cooldownSeconds);
	 event Withdrawn(address indexed to, uint256 amount);

	 modifier onlyOwner() {
         	  require(msg.sender == owner, "not owner");
       		   _;
         }

    	 modifier whenNotPaused() {
         	  require(!paused, "paused");
        	  _;
          }

	  receive() external payable {
    	  	    emit Deposited(msg.sender, msg.value);
          }

	  // Explicit deposit function (useful for teaching)
    	  function deposit() external payable {
          	   require(msg.value > 0, "no value");
        	   emit Deposited(msg.sender, msg.value);
           }

}
