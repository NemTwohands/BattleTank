
#include "TankMovementComponent.h"
#include "TankTracks.h"



void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet) {
	if (!ensure(LeftTrackToSet && !RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(AIForwardIntention,TankForward).Z;
	IntendTurnRight(RightThrow);


}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);


}


void UTankMovementComponent::IntendTurnRight(float Throw) {
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
