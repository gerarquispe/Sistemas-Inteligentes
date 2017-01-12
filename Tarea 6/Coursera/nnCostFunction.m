function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network

Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));
                 
% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m


%% calculando H 
nCapas = 2;
thetaStruct.param(1) = struct('theta',Theta1);
thetaStruct.param(2) = struct('theta',Theta2);
AStruct.param(1) = struct('A', [ones(m,1) X]');
ZStruct.param(1) = struct('Z', zeros(1));
for i = 2:nCapas+1
  thetaStruct.param(i-1).theta * AStruct.param(i-1).A;
  ZStruct.param(i).Z = thetaStruct.param(i-1).theta * AStruct.param(i-1).A;
  AStruct.param(i).A = sigmoid(ZStruct.param(i).Z);
  AStruct.param(i).A = [ones(1,m); AStruct.param(i).A];
end
Htheta = AStruct.param(nCapas+1).A(2:end,:)';

YCost = eye(num_labels);
reg = 0;
for i=1:m
  for k=1:num_labels
    J = J + -YCost(y(i),k)*log(Htheta(i,k));
    J = J -(1-YCost(y(i),k))*log(1-Htheta(i,k));
  end
end
J = 1/m*J;

regVar = 0;
for i=1:nCapas 
   sumTemp = thetaStruct.param(i).theta(:,2:end).^2;
   regVar = regVar + sum(sumTemp(:));
%    regVar = regVar + sum((thetaStruct.param(i).theta(:,2:end).^2)(:));      
end
regVar = lambda/(2*m)*regVar;
J = J + regVar;
   
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
for t=1:m
  %paso 1
  a_1 = [1; X(t,:)'];
  z_2 = Theta1*a_1;
  a_2 = sigmoid(z_2);
  
  % paso 2
  a_2 = [1; a_2];
  z_3 = Theta2*a_2;
  a_3 = sigmoid(z_3);
  delta_3 = a_3 - YCost(:,y(t));
  
  % paso 3
  delta_2 = ((Theta2(:,2:end))')*delta_3 .* sigmoidGradient(z_2);
%  delta_2 = Theta2'*delta_3 .* sigmoidGradient([1;z_2]);
%  delta_2 = delta_2(2:end);
 
  % paso 4  
  Theta1_grad = Theta1_grad + delta_2*a_1';
  Theta2_grad = Theta2_grad + delta_3*a_2';  
end

Theta1_grad = 1/m*Theta1_grad;
Theta2_grad = 1/m*Theta2_grad;

% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%


Theta1_grad(:,2:end) = Theta1_grad(:,2:end) + lambda/m*Theta1(:,2:end);
Theta2_grad(:,2:end) = Theta2_grad(:,2:end) + lambda/m*Theta2(:,2:end);

% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end